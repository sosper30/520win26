# HW4 Assignment

Within your private Github repository called `520-Assignments`, please make a new directory called `hw_4`.

**Note:** For this assignment, you will want to clone the code from Lecture 4, specifically the package `typed_array`.

---

## Requirements

1.  Add the methods `push`, `pop`, `push_front`, and `pop_front` to the `TypedArray` class. Be sure to write your tests first. The arguments to these functions should be declared as `const`. The `pop` methods should return `ElementType` or throw `std::range_error` with the message `"Cannot pop from an empty array"`.

2.  Add a method `TypedArray concat(const TypedArray& other);` to the `TypedArray` class. It should return a new array that is a concatenation of the `this` array and the `other` array, leaving both original arrays untouched. For example:
    ```cpp
    TypedArray<int> a;
    a.set(0, 0);
    a.set(1, 1);
    TypedArray<int> b = a.concat(a).concat(a); // yields a new array [0,1,0,1,0,1]
                                               // a should remain [0,1].
    ```

3.  Define a `TypedArray` method called `reverse` that reverses the array in-place. It should modify the array it is called on and return a reference to the array itself (i.e., `return *this;`).

4.  Overload the `+` operator for the `TypedArray` class to perform concatenation. You should be able to replace the `concat` example line with the following:
    ```cpp
    TypedArray<int> b = a + a + a; // yields a new array [0,1,0,1,0,1]
    ```

---

5.  Implement a `Matrix` class with following requirements:

## Requirements

### Data Members (Private)
- Store matrix elements using `std::vector<double>` in row-major order
- Number of rows and columns
- `EPSILON` constant for floating-point comparisons

### Constructors
```cpp
Matrix();                              // Default: 0×0 empty matrix
Matrix(size_t rows, size_t cols);     // Zero-initialized matrix of given size
Matrix(size_t rows, size_t cols, double value); // Matrix filled with specified value
Matrix(std::initializer_list<std::initializer_list<double>> list); // Construct from 2D initializer list
Matrix(const Matrix& other);           // Copy constructor (deep copy)
```

The default constructor creates an empty matrix with no elements. The size constructor creates a matrix with the specified dimensions, initialized to zero. The value constructor fills all elements with a given value. The initializer list constructor allows convenient syntax like `Matrix m = {{1, 2}, {3, 4}};`. The copy constructor creates an independent copy of another matrix.

### Assignment Operator
```cpp
Matrix& operator=(const Matrix& other); // Copy assignment
```
### Element Access
```cpp
double& operator()(size_t row, size_t col);              // Non-const access
const double& operator()(size_t row, size_t col) const;  // Const access
double& at(size_t row, size_t col);                      // With bounds checking (throw std::out_of_range)
const double& at(size_t row, size_t col) const;
```

### Size and Properties
```cpp
size_t rows() const;
size_t cols() const;
bool isEmpty() const;
bool isSquare() const;
```

### Arithmetic Operators
```cpp
Matrix operator+(const Matrix& other) const;  // Addition
Matrix operator-(const Matrix& other) const;  // Subtraction
Matrix operator*(const Matrix& other) const;  // Matrix multiplication
Matrix operator*(double scalar) const;        // Scalar multiplication
friend Matrix operator*(double scalar, const Matrix& m); // Scalar * matrix
Matrix operator/(double scalar) const;        // Scalar division
Matrix operator-() const;                     // Unary negation
```

### Compound Assignment Operators
```cpp
Matrix& operator+=(const Matrix& other);
Matrix& operator-=(const Matrix& other);
Matrix& operator*=(const Matrix& other);
Matrix& operator*=(double scalar);
Matrix& operator/=(double scalar);
```

### Comparison Operators
```cpp
bool operator==(const Matrix& other) const;
bool operator!=(const Matrix& other) const;
```

Use `EPSILON` for floating-point comparisons in `operator==`.

### Matrix Operations
```cpp
Matrix transpose() const;           // Returns M^T
double trace() const;               // Sum of diagonal (square matrices only, throw std::logic_error)
Matrix diagonal() const;            // Extract diagonal as column vector
void fill(double value);            // Fill entire matrix with value
double norm() const;                // Frobenius norm: sqrt(sum of all elements squared)
```

### Static Factory Methods
```cpp
static Matrix identity(size_t n);                        // n×n identity matrix
static Matrix zeros(size_t rows, size_t cols);
static Matrix ones(size_t rows, size_t cols);
static Matrix diagonal(const std::vector<double>& diag); // Diagonal matrix from vector
```

## Implementation Notes

### Index Calculation for 1D Storage
For row-major order: `index = row * num_cols + col`

### Exception Handling
- Use `std::invalid_argument` for dimension mismatches
- Use `std::out_of_range` for bounds checking in `at()`
- Use `std::logic_error` for operations on wrong matrix types (e.g., trace on non-square)

### Const-Correctness
- All non-modifying methods must be marked `const`
- Provide both const and non-const versions of element access

## Testing Requirements

Write comprehensive tests for:
1. **All constructors** - including edge cases (empty matrix, 1×1, initializer list with unequal rows)
2. **Copy semantics** - verify deep copy (modifying copy doesn't affect original)
3. **Element access** - valid access and bounds checking exceptions
4. **All operators** - including dimension mismatches
5. **Matrix operations** - transpose, trace, diagonal, norm
6. **Static factory methods** - identity, zeros, ones, diagonal
7. **Edge cases** - empty matrices, single elements, non-square matrices
8. **Mathematical properties** - e.g., `(A^T)^T = A`, `A + 0 = A`, `trace(I_n) = n`

## File Structure
```
matrix.h       // Class declaration
matrix.cc      // Implementation
unit_tests.cc  // Google Test unit tests
Makefile       // Build configuration
```

## Example Usage
```cpp
Matrix A = {{1, 2}, {3, 4}};
Matrix B = {{5, 6}, {7, 8}};

Matrix C = A + B;           // Addition
Matrix D = A * B;           // Matrix multiplication
Matrix E = 2.0 * A;         // Scalar multiplication
Matrix F = A.transpose();   // Transpose
double tr = A.trace();      // Trace
double n = A.norm();        // Norm
```

Your hw_4 directory should look like:

matrix.h
matrix.cc
main.cc
Makefile
typed_array.h
unit_tests.cc

Use `unit_tests.cc` for all of your tests (we'll replace it with ours later).
