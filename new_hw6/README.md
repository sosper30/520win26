# HW6 Assignment: Stopwatch, Elma Processes, and LLM Tool Use Agent

## Overview

This assignment has three parts:
1. **Stopwatch class** - A high-precision timer for measuring execution time
2. **Process composition** - Random number generation, filtering, and integration using the ELMA framework
3. **LLM Tool Use Agent** - A C++ application integrating with OpenAI's GPT API using function calling

---

## Part 1: Stopwatch Class

Develop a Stopwatch class that can be used to time functions. The class should have the following methods:
```cpp
void start();              // starts the timer
void stop();               // stops the timer
void reset();              // sets stopwatch to zero
double get_minutes();      // number of minutes counted, as a double
double get_seconds();      // number of seconds counted, as a double
double get_milliseconds(); // number of milliseconds counted, as a double
double get_nanoseconds();  // number of nanoseconds counted, as a double
```

All `get_` methods should return values accurate to the nanosecond. Here is an example usage:
```cpp
#define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

Stopwatch w; // should set the stopwatch to 0 seconds
w.start();
SLEEP;
w.stop();
std::cout << w.get_seconds() << "\n"; // about 1.5
SLEEP;
std::cout << w.get_seconds() << "\n"; // still about 1.5
w.start();
SLEEP;
w.stop();
std::cout << w.get_seconds() << "\n"; // about 3.0
w.reset();
std::cout << w.get_seconds() << "\n"; // 0.0
```

To test your method, we will use assertions that test that `get_seconds` (for example) is approximately equal to the number of seconds that the stopwatch should have counted after various sleep operations.

---

## Part 2: Process Composition with ELMA

In this exercise you will define two processes and compose them with a channel.

### RandomProcess
Define a process called `RandomProcess` that sends random doubles between 0 and 1 (inclusive) to a channel called `link`. It should send a new value to the channel every time it updates.

### Filter
Define another process called `Filter` that reads from the `link` channel and keeps a running average (presumably in a private variable) of the last 10 numbers sent to it (if 10 numbers have not yet been received, the running average should be of the numbers received so far). Initialize the running average to 0.

Add a new method to the `Filter` process called `double value()` that returns the current running average.

The following code should compile:
```cpp
elma::Manager m;

RandomProcess r("random numbers");
Filter f("filter");
elma::Channel link("link");

m.schedule(r, 1_ms)
 .schedule(f, 1_ms)
 .add_channel(link)
 .init()
 .run(100_ms);
```

To test your two processes, we will create various test process classes. For example, we might create a process that alternatively sends 0.25 and 0.75 to the `link` channel. Then we would check that after 100 steps, your `Filter` channel's `value` method returns 0.5.

### Integrator
Define an `Integrator` process that numerically integrates whatever values it reads from a channel called `link`. The integrator should have an initial value equal to zero. When it reads a value `v` from the `link` channel, it should add `delta() * v` to the integrated value (presumably a private variable). 

Add a new method to the `Integrator` process called `double value()` that returns the current integral. 

We will test your process by composing it with a process that sends values to the `link` channel and checks that your process is computing the integral correctly. Thus, you should write such tests as well. For example, you could make a process that outputs a constant value, and check that your integrator outputs a ramp.

---

## Part 3: LLM Tool Use Agent with C++

Build a C++ application that integrates with OpenAI's GPT API using **tool use (function calling)**. Instead of just asking the LLM questions, you'll create custom tools/functions that the LLM can intelligently request and use to solve real problems.

### What is Tool Use?

#### Without Tools
```
User: "What's the weather in Seattle today and what should I wear?"
LLM: "Seattle is usually cool and rainy, so wear a jacket."
     (But it doesn't know TODAY's weather - this is a guess based on historical data)
```

#### With Tools
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

#### Multi-hop Reasoning
```
User: "Plan a trip to Seattle. What should I pack and what indoor activities are there?"

Step 1: LLM calls get_weather_forecast("Seattle", days=7)
        → Returns: forecast data with rain expected
        
Step 2: LLM calls find_indoor_activities("Seattle")
        → Returns: museums, restaurants, theaters, etc.
        
Step 3: LLM provides final response combining both results
```

The LLM acts as a **decision-maker** (what tools to use), while your code is the **executor** (provides accurate data and operations).

### OpenAI Tool Use Format

OpenAI expects tools to be defined as JSON with:
- **name**: identifier for the tool
- **description**: what the tool does
- **parameters**: what inputs it accepts (types, required fields, descriptions)

The LLM then responds by requesting specific tools with specific arguments. You execute those tools, return results, and the LLM continues or provides a final answer.

### Getting Your OpenAI API Key

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

### What You Need to Build

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

### Test Queries

Three test queries you can use are as follows:

1. `"What's 2847 * 3921?"`

2. `"Find the mean and standard deviation of: 23, 45, 67, 12, 89, 34, 56, 78"`

3. `"Generate the first 20 Fibonacci numbers, then calculate their mean and median."`
   - LLM must call Fibonacci tool first
   - Then use that result to call statistics tool
   - Tests your framework's ability to handle multi-step reasoning

---

## Submission Requirements

For Part 1 and Part 2, Your homework directory should contain:
```
stopwatch.cc
stopwatch.h
random_process.cc
random_process.h
filter.cc
filter.h
integrator.cc
integrator.h
Makefile
main.cc
unit_tests.cc
```

The .cc files are optional. You can put all the implementations in the .h if you want.

For Part 3, implement the LLM agent in `llm_agent.cpp`.

### Checklist
- [ ] **Part 1**: Stopwatch class correctly implemented with nanosecond precision
- [ ] **Part 2**: RandomProcess, Filter, and Integrator processes work correctly
- [ ] **Part 3**: Code compiles without errors
- [ ] **Part 3**: Tools correctly implemented (calculator, statistics, Fibonacci)
- [ ] **Part 3**: Tool use loop handles multi-step reasoning
- [ ] **Part 3**: Error handling for invalid inputs and missing tools
- [ ] **Part 3**: Conversation history maintained correctly
- [ ] Clear code with comments throughout all parts
- [ ] Setup and running instructions included

---

## Resources

### LLM Tool Use
- [OpenAI Function Calling Guide](https://platform.openai.com/docs/guides/function-calling)
- [OpenAI API Reference](https://platform.openai.com/docs/api-reference)