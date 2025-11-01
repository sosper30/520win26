#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// g++ -std=c++17 temperature_tool_answer_key.cpp -lcurl -o temperature_tool
// ./temperature_tool

// ============================================================================
// CURL HTTP Request Handler (PROVIDED - Use this for your homework too!)
// ============================================================================

class CurlHandler {
private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
        userp->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

public:
    static std::string makeRequest(const std::string& url, const json& payload, const std::string& api_key) {
        CURL* curl = curl_easy_init();
        if (!curl) throw std::runtime_error("Failed to initialize CURL");

        std::string readBuffer;
        std::string auth_header = "Authorization: Bearer " + api_key;
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, auth_header.c_str());

        std::string payload_str = payload.dump();
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            throw std::runtime_error(std::string("CURL error: ") + curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return readBuffer;
    }
};

// ============================================================================
// SOLUTION CODE
// ============================================================================

const std::string API_URL = "https://api.openai.com/v1/chat/completions";

// Temperature converter function
json convert_temperature(double temp, const std::string& from_unit, 
                        const std::string& to_unit) {
    double result;
    
    // Handle same unit conversion
    if (from_unit == to_unit) {
        result = temp;
    }
    // Celsius to Fahrenheit: F = C * 9/5 + 32
    else if (from_unit == "celsius" && to_unit == "fahrenheit") {
        result = (temp * 9.0 / 5.0) + 32.0;
    }
    // Fahrenheit to Celsius: C = (F - 32) * 5/9
    else if (from_unit == "fahrenheit" && to_unit == "celsius") {
        result = (temp - 32.0) * 5.0 / 9.0;
    }
    else {
        return {{"error", "Invalid unit conversion"}};
    }
    
    return {{"result", result}};
}

// Tool definition for OpenAI API
json get_tool_definition() {
    return json::array({
        {
            {"type", "function"},
            {"function", {
                {"name", "temperature_converter"},
                {"description", "Converts temperature between Celsius and Fahrenheit"},
                {"parameters", {
                    {"type", "object"},
                    {"properties", {
                        {"temperature", {
                            {"type", "number"},
                            {"description", "The temperature value to convert"}
                        }},
                        {"from_unit", {
                            {"type", "string"},
                            {"enum", json::array({"celsius", "fahrenheit"})},
                            {"description", "The unit to convert from"}
                        }},
                        {"to_unit", {
                            {"type", "string"},
                            {"enum", json::array({"celsius", "fahrenheit"})},
                            {"description", "The unit to convert to"}
                        }}
                    }},
                    {"required", json::array({"temperature", "from_unit", "to_unit"})}
                }}
            }}
        }
    });
}

int main() {
    std::string api_key = std::getenv("OPENAI_API_KEY") ?: "";
    if (api_key.empty()) {
        std::cerr << "Error: Set OPENAI_API_KEY environment variable" << std::endl;
        return 1;
    }
    
    std::cout << "=== LLM Tool Calling Demo ===" << std::endl;
    
    // Step 1: Create initial request to LLM
    json messages = json::array({
        {{"role", "user"}, {"content", "What is 25 degrees Celsius in Fahrenheit?"}}
    });
    
    json request = {
        {"model", "gpt-4o-mini"},
        {"messages", messages},
        {"tools", get_tool_definition()}
    };
    
    std::cout << "\n[1] Sending query to LLM..." << std::endl;
    
    // Step 2: Call API
    try {
        std::string response_str = CurlHandler::makeRequest(API_URL, request, api_key);
        json response = json::parse(response_str);
        
        std::cout << "[2] LLM responded" << std::endl;
        
        // Check for API errors
        if (response.contains("error")) {
            std::cerr << "API Error: " << response["error"]["message"] << std::endl;
            return 1;
        }
        
        // Step 3: Check if LLM wants to use tool
        std::string finish_reason = response["choices"][0]["finish_reason"];
        json assistant_message = response["choices"][0]["message"];
        
        if (finish_reason == "tool_calls") {
            std::cout << "[3] LLM wants to use a tool!" << std::endl;
            
            // Extract tool call information
            auto tool_calls = assistant_message["tool_calls"];
            auto tool_call = tool_calls[0];
            
            std::string tool_name = tool_call["function"]["name"];
            std::string tool_call_id = tool_call["id"];
            
            // Parse arguments (they come as a JSON string)
            std::string args_str = tool_call["function"]["arguments"];
            json args = json::parse(args_str);
            
            std::cout << "    Tool: " << tool_name << std::endl;
            std::cout << "    Arguments: " << args.dump() << std::endl;
            
            // Step 4: Execute the tool
            double temperature = args["temperature"];
            std::string from_unit = args["from_unit"];
            std::string to_unit = args["to_unit"];
            
            json result = convert_temperature(temperature, from_unit, to_unit);
            std::cout << "[4] Tool executed. Result: " << result.dump() << std::endl;
            
            // Step 5: Send result back to LLM
            std::cout << "[5] Sending tool result back to LLM..." << std::endl;
            
            // Add assistant message with tool_calls
            json assistant_msg = {
                {"role", "assistant"},
                {"tool_calls", tool_calls}
            };
            // Only add content if it exists and is not null
            if (assistant_message.contains("content") && !assistant_message["content"].is_null()) {
                assistant_msg["content"] = assistant_message["content"];
            }
            messages.push_back(assistant_msg);
            
            // Add tool result message
            messages.push_back({
                {"role", "tool"},
                {"tool_call_id", tool_call_id},
                {"content", result.dump()}
            });
            
            // Make second API call
            json second_request = {
                {"model", "gpt-4o-mini"},
                {"messages", messages}
            };
            
            std::string second_response_str = CurlHandler::makeRequest(API_URL, second_request, api_key);
            json second_response = json::parse(second_response_str);
            
            // Step 6: Print final answer
            if (second_response.contains("error")) {
                std::cerr << "API Error: " << second_response["error"]["message"] << std::endl;
                return 1;
            }
            
            std::string final_answer = second_response["choices"][0]["message"]["content"];
            std::cout << "[6] Final answer: " << final_answer << std::endl;
            
        } else if (finish_reason == "stop") {
            // LLM answered directly without using tool
            std::string direct_answer = assistant_message["content"];
            std::cout << "[3] LLM answered directly (no tool used): " << direct_answer << std::endl;
        } else {
            std::cout << "Unexpected finish_reason: " << finish_reason << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}