# HW1 Assignment

## Instructions

Make a new directory in your `hw_1` directory called `complex`. Make a header file called `complex.h`. Similar to the `fraction.h` file, define a structure called `complex` with two members, `real` and `im`, which should have type `double`. 

You will also need to define a second structure called `polar` with two members: `r` (magnitude) and `theta` (angle in radians), both of type `double`.

Add function prototypes for the following functions:

**Basic operations:**
- `add` - adds two complex numbers
- `subtract` - subtracts two complex numbers  
- `negate` - negates a complex number
- `multiply` - multiplies two complex numbers
- `divide` - divides two complex numbers
- `conjugate` - returns the complex conjugate
- `to_polar` - converts to polar form (returns a `struct polar`)
- `power` - raises a complex number to an integer power
- `magnitude` - returns the magnitude (returns `double`)

**Comparison functions (return `int`, where 1 = true, 0 = false):**
- `equals` - checks if two complex numbers are equal
- `is_real` - checks if imaginary part is zero
- `is_imaginary` - checks if real part is zero (but not both parts)
- `is_zero` - checks if both parts are zero

Functions that return a scalar should return `double`. Functions that return a complex number should return `struct complex`. The `to_polar` function should return `struct polar`.

Next, make a source file called `complex.c` and put the definitions of the functions into it. For the magnitude function you will need a square root function, which can be obtained by adding the C math library as follows:

`#include <math.h>`

at the top of your `complex.c` file. The function itself is called `sqrt` and takes one argument. You will also need `atan2(y, x)` for the polar conversion and `fabs(x)` for absolute value.

### Important Implementation Notes:

- **Division by zero**: In your `divide` function, handle division by zero. Return `INFINITY` for both real and imaginary parts if so.
- **Power function**: Your function must support negative exponents.

Write tests covering normal cases, edge cases (zeros, negatives), and boundary conditions.

Remember, we will compile your code against our own tests, so be sure to name your functions and struct members exactly as specified here and to test edge cases.

**Note:** Your `hw_1` directory should have one sub-directory - `complex`, with its own code and Makefile. You can copy Makefile, main.cpp, and unit_test.cpp from fractions to complex initially. You will need to edit the Makefile to change the word fractions to the word complex. And you will need to replace the tests in unit_test.cpp with your own tests. 

