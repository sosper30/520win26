#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <cmath>
#include <numeric>
#include <algorithm>

using json = nlohmann::json;

// ============================================================================
// SECTION 1: Math Tool Functions
// ============================================================================

class MathTools {
public:
    // Basic calculator
    static json calculator(double a, double b, const std::string& operation) {
        double result;
        if (operation == "add") result = a + b;
        else if (operation == "subtract") result = a - b;
        else if (operation == "multiply") result = a * b;
        else if (operation == "divide") {
            if (b == 0) return {{"error", "Division by zero"}};
            result = a / b;
        }
        else return {{"error", "Unknown operation"}};
        return {{"result", result}};
    }

    // Fibonacci sequence generator
    static json fibonacci_sequence(int n) {
        if (n <= 0) return {{"error", "n must be positive"}};
        if (n > 10000) return {{"error", "n too large"}};
        
        std::vector<double> sequence;
        if (n >= 1) sequence.push_back(0);
        if (n >= 2) sequence.push_back(1);
        
        for (int i = 2; i < n; ++i) {
            sequence.push_back(sequence[i-1] + sequence[i-2]);
        }
        
        return {{"sequence", sequence}, {"count", n}};
    }

    // Statistical calculations
    static json calculate_statistics(const std::vector<double>& numbers) {
        if (numbers.empty()) return {{"error", "Empty vector"}};
        
        double mean = std::accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();
        
        double variance = 0.0;
        for (double x : numbers) {
            variance += (x - mean) * (x - mean);
        }
        variance /= numbers.size();
        double std_dev = std::sqrt(variance);
        
        std::vector<double> sorted = numbers;
        std::sort(sorted.begin(), sorted.end());
        double median;
        if (sorted.size() % 2 == 0) {
            median = (sorted[sorted.size()/2 - 1] + sorted[sorted.size()/2]) / 2.0;
        } else {
            median = sorted[sorted.size()/2];
        }
        
        double min_val = *std::min_element(sorted.begin(), sorted.end());
        double max_val = *std::max_element(sorted.begin(), sorted.end());
        
        return {
            {"mean", mean},
            {"std_dev", std_dev},
            {"median", median},
            {"min", min_val},
            {"max", max_val},
            {"count", numbers.size()}
        };
    }

};

// ============================================================================
// SECTION 2: API Communication Layer
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
// SECTION 3: Tool Definition & Execution Framework
// ============================================================================

class ToolRegistry {
private:
    std::map<std::string, std::function<json(const json&)>> tools;

public:
    ToolRegistry() {
        // Register all tools
        registerTool("calculator", [](const json& args) {
            return MathTools::calculator(
                args["a"], args["b"], args["operation"]
            );
        });

        registerTool("fibonacci_sequence", [](const json& args) {
            return MathTools::fibonacci_sequence(args["n"]);
        });

        registerTool("calculate_statistics", [](const json& args) {
            std::vector<double> nums = args["numbers"].get<std::vector<double>>();
            return MathTools::calculate_statistics(nums);
        });
    }

    void registerTool(const std::string& name, std::function<json(const json&)> fn) {
        tools[name] = fn;
    }

    json executeTool(const std::string& name, const json& args) {
        if (tools.find(name) == tools.end()) {
            return {{"error", "Tool not found: " + name}};
        }
        return tools[name](args);
    }

    json getToolDefinitions() {
        return json::array({
            {
                {"type", "function"},
                {"function", {
                    {"name", "calculator"},
                    {"description", "Performs basic arithmetic operations"},
                    {"parameters", {
                        {"type", "object"},
                        {"properties", {
                            {"a", {{"type", "number"}, {"description", "First operand"}}},
                            {"b", {{"type", "number"}, {"description", "Second operand"}}},
                            {"operation", {
                                {"type", "string"},
                                {"enum", json::array({"add", "subtract", "multiply", "divide"})},
                                {"description", "Operation to perform"}
                            }}
                        }},
                        {"required", json::array({"a", "b", "operation"})}
                    }}
                }}
            },
            {
                {"type", "function"},
                {"function", {
                    {"name", "fibonacci_sequence"},
                    {"description", "Generates first n Fibonacci numbers"},
                    {"parameters", {
                        {"type", "object"},
                        {"properties", {
                            {"n", {{"type", "integer"}, {"description", "Number of Fibonacci terms"}}}
                        }},
                        {"required", json::array({"n"})}
                    }}
                }}
            },
            {
                {"type", "function"},
                {"function", {
                    {"name", "calculate_statistics"},
                    {"description", "Calculates mean, std dev, median, min, max of a dataset"},
                    {"parameters", {
                        {"type", "object"},
                        {"properties", {
                            {"numbers", {
                                {"type", "array"},
                                {"items", {{"type", "number"}}},
                                {"description", "Array of numbers"}
                            }}
                        }},
                        {"required", json::array({"numbers"})}
                    }}
                }}
            },
        });
    }
};

// ============================================================================
// SECTION 4: Tool Use Agent Loop
// ============================================================================

class LLMAgent {
private:
    std::string api_key;
    ToolRegistry tool_registry;
    const std::string API_URL = "https://api.openai.com/v1/chat/completions";
    std::vector<json> conversation_history;
    int max_iterations = 10;

public:
    LLMAgent(const std::string& key) : api_key(key) {}

    json processUserQuery(const std::string& user_query) {
        conversation_history.clear();
        conversation_history.push_back({
            {"role", "user"},
            {"content", user_query}
        });

        std::cout << "\n=== LLM Agent Tool Use Loop ===" << std::endl;
        std::cout << "User Query: " << user_query << std::endl;

        for (int iteration = 0; iteration < max_iterations; ++iteration) {
            std::cout << "\n--- Iteration " << (iteration + 1) << " ---" << std::endl;

            // Step 1: Call LLM
            json response = callLLM();
            
            if (response.contains("error")) {
                std::cerr << "API Error: " << response["error"] << std::endl;
                return {{"error", response["error"]}};
            }

            std::string stop_reason = response["choices"][0]["finish_reason"];
            json message = response["choices"][0]["message"];

            std::cout << "LLM Response (finish_reason: " << stop_reason << ")" << std::endl;

            // Step 2: Check if LLM wants to use tools
            if (stop_reason == "tool_calls") {
                auto tool_calls = message.contains("tool_calls") ? message["tool_calls"] : json::array();
                
                if (tool_calls.is_null() || tool_calls.empty()) {
                    std::cout << "Error: finish_reason is tool_calls but no tool_calls found" << std::endl;
                    break;
                }

                // Add assistant message to history (with tool_calls)
                conversation_history.push_back({
                    {"role", "assistant"},
                    {"content", message.contains("content") ? message["content"] : ""},
                    {"tool_calls", tool_calls}
                });

                // Step 3: Execute each tool call and collect results
                for (const auto& tool_call : tool_calls) {
                    std::string tool_name = tool_call["function"]["name"];
                    std::string tool_use_id = tool_call["id"];
                    
                    // Parse arguments - handle both string and json formats
                    json tool_args;
                    auto args_value = tool_call["function"]["arguments"];
                    if (args_value.is_string()) {
                        tool_args = json::parse(args_value.get<std::string>());
                    } else {
                        tool_args = args_value;
                    }

                    std::cout << "Executing tool: " << tool_name << std::endl;
                    std::cout << "Arguments: " << tool_args.dump(2) << std::endl;

                    json result = tool_registry.executeTool(tool_name, tool_args);
                    std::cout << "Tool Result: " << result.dump(2) << std::endl;

                    // Step 4: Add tool result to history
                    conversation_history.push_back({
                        {"role", "tool"},
                        {"tool_call_id", tool_use_id},
                        {"content", result.dump()}
                    });
                }

            } else if (stop_reason == "end_turn" || stop_reason == "stop") {
                // Final response from LLM
                std::string final_response = message.contains("content") ? 
                    message["content"].get<std::string>() : "No response";
                std::cout << "Final LLM Response: " << final_response << std::endl;
                
                return {{"success", true}, {"final_response", final_response}};
                
            } else {
                std::cout << "Unexpected stop reason: " << stop_reason << std::endl;
                break;
            }
        }

        return {{"error", "Max iterations reached"}};
    }

private:
    json callLLM() {
        json payload = {
            {"model", "gpt-4o-mini"},
            {"messages", conversation_history},
            {"tools", tool_registry.getToolDefinitions()},
            {"tool_choice", "auto"},
            {"temperature", 0.7}
        };

        try {
            std::string response_str = CurlHandler::makeRequest(API_URL, payload, api_key);
            return json::parse(response_str);
        } catch (const std::exception& e) {
            return {{"error", e.what()}};
        }
    }
};

// ============================================================================
// SECTION 5: Main Program
// ============================================================================

int main() {
    std::string api_key = std::getenv("OPENAI_API_KEY") ?: "";
    if (api_key.empty()) {
        std::cerr << "Error: OPENAI_API_KEY environment variable not set" << std::endl;
        return 1;
    }

    LLMAgent agent(api_key);

    // Test queries
    std::vector<std::string> queries = {
        "What's 2847 * 3921?",
        "Find the mean and standard deviation of: 23, 45, 67, 12, 89, 34, 56, 78",
        "Generate the first 20 Fibonacci numbers, then calculate their mean and median."
    };

    for (const auto& query : queries) {
        json result = agent.processUserQuery(query);
        std::cout << "\n=== Final Result ===" << std::endl;
        std::cout << result.dump(2) << std::endl;
        std::cout << "\n" << std::string(60, '=') << "\n" << std::endl;
    }

    return 0;
}