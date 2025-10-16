#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <cstddef>

class Matrix {
private:
    std::vector<double> data_;
    size_t num_rows_;
    size_t num_cols_;
    
    static constexpr double EPSILON = 1e-9;
    
    // Helper function to calculate 1D index from 2D coordinates
    size_t getIndex(size_t row, size_t col) const;
    
    // Helper function for floating-point comparison
    bool almostEqual(double a, double b) const;

public:
    // ========== CONSTRUCTORS & DESTRUCTOR ==========
    
    // Default constructor: creates empty 0x0 matrix
    Matrix();
    
    // Create matrix of given size (zero-initialized)
    Matrix(size_t rows, size_t cols);
    
    // Create matrix filled with specific value
    Matrix(size_t rows, size_t cols, double value);
    
    // Create from initializer list
    // Example: Matrix m = {{1, 2}, {3, 4}};
    Matrix(std::initializer_list<std::initializer_list<double>> list);
    
    // Copy constructor
    Matrix(const Matrix& other);
    
    // Destructor (using std::vector so default is fine, but declared for completeness)
    ~Matrix() = default;
    
    // ========== ASSIGNMENT OPERATORS ==========
    
    // Copy assignment
    Matrix& operator=(const Matrix& other);
    
    // ========== ELEMENT ACCESS ==========
    
    // Access element (no bounds checking)
    double& operator()(size_t row, size_t col);
    const double& operator()(size_t row, size_t col) const;
    
    // Access with bounds checking
    double& at(size_t row, size_t col);
    const double& at(size_t row, size_t col) const;
    
    // ========== SIZE AND PROPERTIES ==========
    
    size_t rows() const;
    size_t cols() const;
    bool isEmpty() const;
    bool isSquare() const;
    
    // ========== ARITHMETIC OPERATORS ==========
    
    // Matrix addition
    Matrix operator+(const Matrix& other) const;
    
    // Matrix subtraction
    Matrix operator-(const Matrix& other) const;
    
    // Matrix multiplication
    Matrix operator*(const Matrix& other) const;
    
    // Scalar multiplication (matrix * scalar)
    Matrix operator*(double scalar) const;
    
    // Scalar multiplication (scalar * matrix)
    friend Matrix operator*(double scalar, const Matrix& m);
    
    // Scalar division
    Matrix operator/(double scalar) const;
    
    // Unary negation
    Matrix operator-() const;
    
    // ========== COMPOUND ASSIGNMENT OPERATORS ==========
    
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);
    
    // ========== COMPARISON OPERATORS ==========
    
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    
    // ========== MATRIX OPERATIONS ==========
    
    // Transpose
    Matrix transpose() const;
    
    // Trace (sum of diagonal elements, square matrices only)
    double trace() const;
    
    // Extract diagonal as column vector
    Matrix diagonal() const;
    
    // Fill matrix with value
    void fill(double value);
    
    // Frobenius norm
    double norm() const;
    
    // ========== STATIC FACTORY METHODS ==========
    
    // Create n×n identity matrix
    static Matrix identity(size_t n);
    
    // Create matrix of zeros
    static Matrix zeros(size_t rows, size_t cols);
    
    // Create matrix of ones
    static Matrix ones(size_t rows, size_t cols);
    
    // Create diagonal matrix from vector
    static Matrix diagonal(const std::vector<double>& diag);
    
    // ========== STREAM OPERATORS ==========
    
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
    friend std::istream& operator>>(std::istream& is, Matrix& m);
};

#endif // MATRIX_H