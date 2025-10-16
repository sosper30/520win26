#include "matrix.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include <algorithm>

// ========== PRIVATE HELPER METHODS ==========

size_t Matrix::getIndex(size_t row, size_t col) const {
    return row * num_cols_ + col;
}

bool Matrix::almostEqual(double a, double b) const {
    return std::abs(a - b) < EPSILON;
}

// ========== CONSTRUCTORS ==========

// Default constructor: creates empty 0x0 matrix
Matrix::Matrix() : num_rows_(0), num_cols_(0) {}

// Create matrix of given size (zero-initialized)
Matrix::Matrix(size_t rows, size_t cols) 
    : data_(rows * cols, 0.0), num_rows_(rows), num_cols_(cols) {}

// Create matrix filled with specific value
Matrix::Matrix(size_t rows, size_t cols, double value)
    : data_(rows * cols, value), num_rows_(rows), num_cols_(cols) {}

// Create from initializer list
Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list) {
    num_rows_ = list.size();
    if (num_rows_ == 0) {
        num_cols_ = 0;
        return;
    }
    
    num_cols_ = list.begin()->size();
    data_.reserve(num_rows_ * num_cols_);
    
    for (const auto& row : list) {
        if (row.size() != num_cols_) {
            throw std::invalid_argument("All rows must have the same number of columns");
        }
        for (double val : row) {
            data_.push_back(val);
        }
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& other)
    : data_(other.data_), num_rows_(other.num_rows_), num_cols_(other.num_cols_) {}

// ========== ASSIGNMENT OPERATORS ==========

// Copy assignment
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        data_ = other.data_;
        num_rows_ = other.num_rows_;
        num_cols_ = other.num_cols_;
    }
    return *this;
}

// ========== ELEMENT ACCESS ==========

double& Matrix::operator()(size_t row, size_t col) {
    return data_[getIndex(row, col)];
}

const double& Matrix::operator()(size_t row, size_t col) const {
    return data_[getIndex(row, col)];
}

double& Matrix::at(size_t row, size_t col) {
    if (row >= num_rows_ || col >= num_cols_) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data_[getIndex(row, col)];
}

const double& Matrix::at(size_t row, size_t col) const {
    if (row >= num_rows_ || col >= num_cols_) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data_[getIndex(row, col)];
}

// ========== SIZE AND PROPERTIES ==========

size_t Matrix::rows() const {
    return num_rows_;
}

size_t Matrix::cols() const {
    return num_cols_;
}

bool Matrix::isEmpty() const {
    return num_rows_ == 0 || num_cols_ == 0;
}

bool Matrix::isSquare() const {
    return num_rows_ == num_cols_ && num_rows_ > 0;
}

// ========== ARITHMETIC OPERATORS ==========

// Matrix addition
Matrix Matrix::operator+(const Matrix& other) const {
    if (num_rows_ != other.num_rows_ || num_cols_ != other.num_cols_) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    
    Matrix result(num_rows_, num_cols_);
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] + other.data_[i];
    }
    return result;
}

// Matrix subtraction
Matrix Matrix::operator-(const Matrix& other) const {
    if (num_rows_ != other.num_rows_ || num_cols_ != other.num_cols_) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    
    Matrix result(num_rows_, num_cols_);
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] - other.data_[i];
    }
    return result;
}

// Matrix multiplication
Matrix Matrix::operator*(const Matrix& other) const {
    if (num_cols_ != other.num_rows_) {
        throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
    }
    
    Matrix result(num_rows_, other.num_cols_);
    for (size_t i = 0; i < num_rows_; ++i) {
        for (size_t j = 0; j < other.num_cols_; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < num_cols_; ++k) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

// Scalar multiplication (matrix * scalar)
Matrix Matrix::operator*(double scalar) const {
    Matrix result(num_rows_, num_cols_);
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] * scalar;
    }
    return result;
}

// Scalar multiplication (scalar * matrix)
Matrix operator*(double scalar, const Matrix& m) {
    return m * scalar;
}

// Scalar division
Matrix Matrix::operator/(double scalar) const {
    if (std::abs(scalar) < EPSILON) {
        throw std::invalid_argument("Division by zero");
    }
    return (*this) * (1.0 / scalar);
}

// Unary negation
Matrix Matrix::operator-() const {
    Matrix result(num_rows_, num_cols_);
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = -data_[i];
    }
    return result;
}

// ========== COMPOUND ASSIGNMENT OPERATORS ==========

Matrix& Matrix::operator+=(const Matrix& other) {
    if (num_rows_ != other.num_rows_ || num_cols_ != other.num_cols_) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] += other.data_[i];
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (num_rows_ != other.num_rows_ || num_cols_ != other.num_cols_) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] -= other.data_[i];
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    *this = (*this) * other;
    return *this;
}

Matrix& Matrix::operator*=(double scalar) {
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] *= scalar;
    }
    return *this;
}

Matrix& Matrix::operator/=(double scalar) {
    if (std::abs(scalar) < EPSILON) {
        throw std::invalid_argument("Division by zero");
    }
    *this *= (1.0 / scalar);
    return *this;
}

// ========== COMPARISON OPERATORS ==========

bool Matrix::operator==(const Matrix& other) const {
    if (num_rows_ != other.num_rows_ || num_cols_ != other.num_cols_) {
        return false;
    }
    
    for (size_t i = 0; i < data_.size(); ++i) {
        if (!almostEqual(data_[i], other.data_[i])) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

// ========== MATRIX OPERATIONS ==========

// Transpose
Matrix Matrix::transpose() const {
    Matrix result(num_cols_, num_rows_);
    for (size_t i = 0; i < num_rows_; ++i) {
        for (size_t j = 0; j < num_cols_; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

// Trace
double Matrix::trace() const {
    if (!isSquare()) {
        throw std::logic_error("Trace requires square matrix");
    }
    
    double sum = 0.0;
    for (size_t i = 0; i < num_rows_; ++i) {
        sum += (*this)(i, i);
    }
    return sum;
}

// Extract diagonal
Matrix Matrix::diagonal() const {
    size_t diag_size = std::min(num_rows_, num_cols_);
    Matrix result(diag_size, 1);
    for (size_t i = 0; i < diag_size; ++i) {
        result(i, 0) = (*this)(i, i);
    }
    return result;
}

// Fill matrix with value
void Matrix::fill(double value) {
    std::fill(data_.begin(), data_.end(), value);
}

// Frobenius norm
double Matrix::norm() const {
    double sum = 0.0;
    for (double val : data_) {
        sum += val * val;
    }
    return std::sqrt(sum);
}

// ========== STATIC FACTORY METHODS ==========

Matrix Matrix::identity(size_t n) {
    Matrix result(n, n);
    for (size_t i = 0; i < n; ++i) {
        result(i, i) = 1.0;
    }
    return result;
}

Matrix Matrix::zeros(size_t rows, size_t cols) {
    return Matrix(rows, cols);
}

Matrix Matrix::ones(size_t rows, size_t cols) {
    return Matrix(rows, cols, 1.0);
}

Matrix Matrix::diagonal(const std::vector<double>& diag) {
    size_t n = diag.size();
    Matrix result(n, n);
    for (size_t i = 0; i < n; ++i) {
        result(i, i) = diag[i];
    }
    return result;
}

// ========== STREAM OPERATORS ==========

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    os << "[";
    for (size_t i = 0; i < m.num_rows_; ++i) {
        if (i > 0) os << " ";
        os << "[";
        for (size_t j = 0; j < m.num_cols_; ++j) {
            os << m(i, j);
            if (j < m.num_cols_ - 1) os << ", ";
        }
        os << "]";
        if (i < m.num_rows_ - 1) os << "\n";
    }
    os << "]";
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m) {
    for (size_t i = 0; i < m.num_rows_; ++i) {
        for (size_t j = 0; j < m.num_cols_; ++j) {
            is >> m(i, j);
        }
    }
    return is;
}