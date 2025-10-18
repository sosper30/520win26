## **Objective**
This assignment is designed to reinforce your understanding of C programming fundamentals, modular code organization, and working with header files. You will apply concepts learned in class to create a calculator program that performs various mathematical operations based on user input.

## **Assignment Description**
You will create a calculator program in C that:

1. **Displays a menu** showing all available operations to the user
2. **Accepts an operation choice** from the user by entering a corresponding number:
   * `1` for addition
   * `2` for subtraction
   * `3` for multiplication
   * `4` for division
   * `5` for modulo (remainder)
   * `6` for power (exponentiation)
3. **Accepts two numbers** from the user as input (use floating-point numbers)
4. **Performs the selected operation** and displays the result with appropriate formatting
5. **Exits** after completing one calculation

We've already covered addition in class; your task is to implement the remaining operations (subtraction, multiplication, division, modulo, and power).

## **Requirements**

### **Core Functionality:**
* **Menu Display:** Create a clear, user-friendly menu showing all available operations
* **Floating-Point Support:** Use `double` data type to handle decimal numbers
* **Operation Implementation:** Implement all six mathematical operations:
  - Addition (+)
  - Subtraction (-)
  - Multiplication (*)
  - Division (/)
  - Modulo (%) 
  - Power (^) 
* **Result Display:** Show the calculation in a clear format (e.g., "5.00 + 3.00 = 8.00")

### **Input Validation:**
* Validate that the user's operation choice is within the valid range (1-6)
* Handle **division by zero** gracefully with an appropriate error message
* Handle **modulo by zero** gracefully with an appropriate error message

### **Code Organization:**
* **Header Files:** You must create your own header file(s) to organize your code. These files should contain:
  - Function declarations
  - `#define` constants or macros (if needed)
  - Any other reusable components
* **Modular Programming:** Use modular programming practices to keep your code clean and organized:
  - Separate functionality into functions (e.g., a function to display the menu)
  - Use meaningful names for variables and functions
  - Add comments to explain your code logic

## **Example Output**
```
==========================================
   Welcome to the Enhanced Calculator!   
==========================================

Select an operation:
  1. Addition (+)
  2. Subtraction (-)
  3. Multiplication (*)
  4. Division (/)
  5. Modulo (%)
  6. Power (x^y)
------------------------------------------
Your choice: 4
Enter first number: 10
Enter second number: 3

10.00 / 3.00 = 3.33

Thank you for using the calculator!
```

## **Deliverables**

Submit a **Zip file** which includes:

1. **All Source Code File(s):** `.c` file(s) containing the implementation of the calculator
2. **All Header File(s):** `.h` file(s) used in your program
3. **README (optional):** Brief instructions on how to compile and run your program
