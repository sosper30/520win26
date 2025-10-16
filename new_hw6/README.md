# HW6 Assignment: Using Generative AI in C++: LLM Tool Use Agent with C++

## Overview

Build a C++ application that integrates with OpenAI's GPT API using **tool use (function calling)**. Instead of just asking the LLM questions, you'll create custom tools/functions that the LLM can intelligently request and use to solve real problems.

---

## What is Tool Use?

### Without Tools
```
User: "What's the weather in Seattle today and what should I wear?"
LLM: "Seattle is usually cool and rainy, so wear a jacket."
     (But it doesn't know TODAY's weather - this is a guess based on historical data)
```

### With Tools
```
User: "What's the weather in Seattle today and what should I wear?"
        ↓
    LLM decides: "I need current weather data"
        ↓
Your program: Calls get_weather("Seattle")
        ↓
    Returns: {"temp": 48F, "condition": "rainy", "wind": "10mph"}
        ↓
LLM: "It's 48°F and rainy. Wear a waterproof jacket and bring an umbrella."
```

### Multi-hop Reasoning
```
User: "Plan a trip to Seattle. What should I pack and what indoor activities are there?"

Step 1: LLM calls get_weather_forecast("Seattle", days=7)
        → Returns: forecast data with rain expected
        
Step 2: LLM calls find_indoor_activities("Seattle")
        → Returns: museums, restaurants, theaters, etc.
        
Step 3: LLM provides final response combining both results
```

The LLM acts as a **decision-maker** (what tools to use), while your code is the **executor** (provides accurate data and operations).

---

## OpenAI Tool Use Format

OpenAI expects tools to be defined as JSON with:
- **name**: identifier for the tool
- **description**: what the tool does
- **parameters**: what inputs it accepts (types, required fields, descriptions)

The LLM then responds by requesting specific tools with specific arguments. You execute those tools, return results, and the LLM continues or provides a final answer.

---

## Getting Your OpenAI API Key

1. Go to [https://platform.openai.com/api-keys](https://platform.openai.com/api-keys)
2. Sign up or log in with your OpenAI account
3. Click "Create new secret key"
4. Copy the key (it starts with `sk-`)
5. Store it securely - **never commit it to version control**

Set the key as an environment variable in the docker container:
```bash
export OPENAI_API_KEY="sk-your-key-here"
```

**Important**: Use the `gpt-4o-mini` model in your code. It's very cost-effective:
- Input: $0.15 per 1M tokens
- Output: $0.60 per 1M tokens
- Each test query will cost less than 1 cent

## What You Need to Build

**Tool Framework**: Create C++ tools/functions that your LLM can call. The assignment requires:
- A calculator tool (arithmetic operations)
- A statistics tool (mean, standard deviation, median)
- A Fibonacci sequence generator

**Tool Registry**: A system to register and execute tools dynamically. When the LLM requests a tool, your code looks it up and executes it.

**Agent Loop**: The core loop that:
1. Sends the user query + tool definitions to the LLM
2. Receives the LLM's response (does it want to call a tool?)
3. If yes: parse tool name/arguments, execute it, send results back to LLM
4. If no: LLM has final answer, return to user
5. Repeat until done (with a max iteration limit)

**Message Handling**: Maintain conversation history in the format OpenAI expects. This includes tracking which tools were called and what results were returned.

---

## Test Queries

Three test queries you can use are as follows:

1. `"What's 2847 * 3921?"`

2. `"Find the mean and standard deviation of: 23, 45, 67, 12, 89, 34, 56, 78"`

3. `"Generate the first 20 Fibonacci numbers, then calculate their mean and median."`
   - LLM must call Fibonacci tool first
   - Then use that result to call statistics tool
   - Tests your framework's ability to handle multi-step reasoning

---

## Submission Requirements

- [ ] Code compiles without errors
- [ ] Tools correctly implemented 
- [ ] Tool use loop handles multi-step reasoning
- [ ] Error handling for invalid inputs and missing tools
- [ ] Conversation history maintained correctly
- [ ] Clear code with comments
- [ ] Setup and running instructions included

---

## Resources

- [OpenAI Function Calling Guide](https://platform.openai.com/docs/guides/function-calling)
- [OpenAI API Reference](https://platform.openai.com/docs/api-reference)



