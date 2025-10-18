# ICTE6: Implementing and Testing Custom Sorting Functions

## Objective
Enhance your understanding of the C++ Standard Template Library (STL), particularly vectors, iterators, generic algorithms, and lambda expressions. Practice implementation of sorting functions, algorithm composition, and unit testing.

---

## Task Overview

### **1. Implement Custom Sorting and Transformation Functions**

#### **Function 1: `sort_by_magnitude`**
Write a function that takes a reference to a `std::vector<double>` and sorts it in ascending order based on the absolute values of its elements.
- Use `std::sort` with a lambda expression for custom comparison logic.

#### **Function 2: `partition_by_sign`**
Write a function that partitions a vector into negative and positive numbers while preserving the relative order within each partition.
- Use `std::stable_partition` to maintain order.
- Return an iterator pointing to the first non-negative element.

#### **Function 3: `normalize_and_sort`**
Write a function that normalizes values to the range [-1, 1] and sorts them in ascending order.
- Use `std::max_element` to find the maximum magnitude.
- Use `std::transform` for normalization.
- Use `std::sort` for final sorting.
- Return a new vector (const input).

### **2. Develop Unit Tests**
Create unit tests to verify the correctness of your functions. Cover various scenarios:
- Vectors with positive and negative numbers
- Vectors containing zeros
- Vectors with duplicate absolute values
- Empty vectors
- Edge cases

Use a testing framework of your choice (e.g., Google Test) to write unit tests.
Example using a simple test framework:

```cpp
#include "utilities.h"
#include <iostream>
#include <vector>
#include <cassert>

void test_sort_by_magnitude() {
    {
        std::vector<double> vec = {3.0, -1.0, -2.0, 4.0};
        sort_by_magnitude(vec);
        assert((vec == std::vector<double>{-1.0, -2.0, 3.0, 4.0}));
    }
    {
        std::vector<double> vec = {0.0, -0.0, 0.0};
        sort_by_magnitude(vec);
        assert((vec == std::vector<double>{0.0, -0.0, 0.0}));
    }
    {
        std::vector<double> vec = {};
        sort_by_magnitude(vec);
        assert((vec == std::vector<double>{}));
    }
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test_sort_by_magnitude();
    return 0;
}
```
---

## Function Signatures

```cpp
// utilities.h
void sort_by_magnitude(std::vector<double>& vec);

std::vector<double>::iterator partition_by_sign(std::vector<double>& vec);

std::vector<double> normalize_and_sort(const std::vector<double>& vec);
```

---

## Examples

### **sort_by_magnitude:**
```cpp
std::vector<double> vec = {3.0, -1.0, -2.0, 4.0};
sort_by_magnitude(vec);
// Result: {-1.0, -2.0, 3.0, 4.0}
```

### **partition_by_sign:**
```cpp
std::vector<double> vec = {-1.0, -2.0, 3.0, 4.0, -5.0, 8.0};
auto it = partition_by_sign(vec);
// Result: {-1.0, -2.0, -5.0, 3.0, 4.0, 8.0}
//                            ^ iterator points here
```

### **normalize_and_sort:**
```cpp
std::vector<double> vec = {-10.0, 5.0, -2.0, 8.0};
auto result = normalize_and_sort(vec);
// Result: {-1.0, -0.2, 0.5, 0.8}
```

---

## File Structure

```
assignment/
├── README.md
├── Makefile
├── Doxygen html folder
├── utilities.h: Contains the function declaration.
├── utilities.cpp: Contains the function implementation.
└── unit_tests.cpp: Contains the unit tests.
```

Ensure that your code compiles without errors and passes all tests.
Ensure that each test case is independent and thoroughly checks the function's behavior under different conditions.
Provide detailed optimized comments for Doxygen for your .h and .cpp files and submit the html folder



