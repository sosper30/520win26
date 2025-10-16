#include <math.h>
#include <cmath>
#include <float.h>
#include <assert.h>
#include "matrix.h"
#include "gtest/gtest.h"

namespace {

// ========== CONSTRUCTOR TESTS ==========

TEST(MatrixConstructors, DefaultConstructor) {
    Matrix m;
    EXPECT_EQ(0, m.rows());
    EXPECT_EQ(0, m.cols());
    EXPECT_TRUE(m.isEmpty());
}

TEST(MatrixConstructors, SizeConstructor) {
    Matrix m(3, 4);
    EXPECT_EQ(3, m.rows());
    EXPECT_EQ(4, m.cols());
    EXPECT_FALSE(m.isEmpty());
    
    // Check all elements are zero-initialized
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            EXPECT_DOUBLE_EQ(0.0, m(i, j));
        }
    }
}

TEST(MatrixConstructors, SizeAndValueConstructor) {
    Matrix m(2, 3, 5.0);
    EXPECT_EQ(2, m.rows());
    EXPECT_EQ(3, m.cols());
    
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_DOUBLE_EQ(5.0, m(i, j));
        }
    }
}

TEST(MatrixConstructors, InitializerListConstructor) {
    Matrix m = {{1, 2, 3},
                {4, 5, 6}};
    
    EXPECT_EQ(2, m.rows());
    EXPECT_EQ(3, m.cols());
    EXPECT_DOUBLE_EQ(1.0, m(0, 0));
    EXPECT_DOUBLE_EQ(2.0, m(0, 1));
    EXPECT_DOUBLE_EQ(3.0, m(0, 2));
    EXPECT_DOUBLE_EQ(4.0, m(1, 0));
    EXPECT_DOUBLE_EQ(5.0, m(1, 1));
    EXPECT_DOUBLE_EQ(6.0, m(1, 2));
}

TEST(MatrixConstructors, InitializerListEmpty) {
    Matrix m = {{}};
    EXPECT_EQ(1, m.rows());
    EXPECT_EQ(0, m.cols());
}

TEST(MatrixConstructors, InitializerListSingleElement) {
    Matrix m = {{42}};
    EXPECT_EQ(1, m.rows());
    EXPECT_EQ(1, m.cols());
    EXPECT_DOUBLE_EQ(42.0, m(0, 0));
}

TEST(MatrixConstructors, InitializerListUnequalRows) {
    bool threw = false;
    try {
        Matrix m = {{1, 2, 3},
                    {4, 5}};  // Unequal row sizes
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    EXPECT_TRUE(threw);
}

TEST(MatrixConstructors, CopyConstructor) {
    Matrix m1 = {{1, 2},
                 {3, 4}};
    Matrix m2(m1);
    
    EXPECT_EQ(m1.rows(), m2.rows());
    EXPECT_EQ(m1.cols(), m2.cols());
    EXPECT_EQ(m1, m2);
    
    // Verify deep copy - modify m2 shouldn't affect m1
    m2(0, 0) = 99;
    EXPECT_DOUBLE_EQ(1.0, m1(0, 0));
    EXPECT_DOUBLE_EQ(99.0, m2(0, 0));
}

TEST(MatrixConstructors, CopyAssignment) {
    Matrix m1 = {{1, 2},
                 {3, 4}};
    Matrix m2;
    m2 = m1;
    
    EXPECT_EQ(m1, m2);
    
    // Verify deep copy
    m2(0, 0) = 99;
    EXPECT_DOUBLE_EQ(1.0, m1(0, 0));
}

TEST(MatrixConstructors, SelfAssignment) {
    Matrix m = {{1, 2},
                {3, 4}};
    m = m;  // Should handle self-assignment gracefully
    
    EXPECT_EQ(2, m.rows());
    EXPECT_EQ(2, m.cols());
    EXPECT_DOUBLE_EQ(1.0, m(0, 0));
}

// ========== ADDITION TESTS ==========

TEST(MatrixAddition, BasicAddition) {
    Matrix m1 = {{1, 2},
                 {3, 4}};
    Matrix m2 = {{5, 6},
                 {7, 8}};
    Matrix result = m1 + m2;
    
    EXPECT_EQ(2, result.rows());
    EXPECT_EQ(2, result.cols());
    EXPECT_DOUBLE_EQ(6.0, result(0, 0));
    EXPECT_DOUBLE_EQ(8.0, result(0, 1));
    EXPECT_DOUBLE_EQ(10.0, result(1, 0));
    EXPECT_DOUBLE_EQ(12.0, result(1, 1));
}

TEST(MatrixAddition, AdditionWithNegatives) {
    Matrix m1 = {{1, -2},
                 {-3, 4}};
    Matrix m2 = {{-1, 2},
                 {3, -4}};
    Matrix result = m1 + m2;
    
    EXPECT_DOUBLE_EQ(0.0, result(0, 0));
    EXPECT_DOUBLE_EQ(0.0, result(0, 1));
    EXPECT_DOUBLE_EQ(0.0, result(1, 0));
    EXPECT_DOUBLE_EQ(0.0, result(1, 1));
}

TEST(MatrixAddition, AdditionWithZero) {
    Matrix m1 = {{1, 2},
                 {3, 4}};
    Matrix zero = Matrix::zeros(2, 2);
    Matrix result = m1 + zero;
    
    EXPECT_EQ(m1, result);
}

TEST(MatrixAddition, AdditionNonSquare) {
    Matrix m1 = {{1, 2, 3},
                 {4, 5, 6}};
    Matrix m2 = {{7, 8, 9},
                 {10, 11, 12}};
    Matrix result = m1 + m2;
    
    EXPECT_EQ(2, result.rows());
    EXPECT_EQ(3, result.cols());
    EXPECT_DOUBLE_EQ(8.0, result(0, 0));
    EXPECT_DOUBLE_EQ(10.0, result(0, 1));
    EXPECT_DOUBLE_EQ(12.0, result(0, 2));
}

TEST(MatrixAddition, DimensionMismatchRows) {
    Matrix m1(2, 3);
    Matrix m2(3, 3);
    bool threw = false;
    try {
        Matrix result = m1 + m2;
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    EXPECT_TRUE(threw);
}

TEST(MatrixAddition, DimensionMismatchCols) {
    Matrix m1(3, 2);
    Matrix m2(3, 3);
    bool threw = false;
    try {
        Matrix result = m1 + m2;
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    EXPECT_TRUE(threw);
}

TEST(MatrixAddition, CompoundAddition) {
    Matrix m1 = {{1, 2},
                 {3, 4}};
    Matrix m2 = {{5, 6},
                 {7, 8}};
    Matrix& result = (m1 += m2);
    
    EXPECT_EQ(&m1, &result);  // Should return reference to self
    EXPECT_DOUBLE_EQ(6.0, m1(0, 0));
    EXPECT_DOUBLE_EQ(8.0, m1(0, 1));
    EXPECT_DOUBLE_EQ(10.0, m1(1, 0));
    EXPECT_DOUBLE_EQ(12.0, m1(1, 1));
}

TEST(MatrixAddition, CompoundAdditionChaining) {
    Matrix m1 = {{1, 1},
                 {1, 1}};
    Matrix m2 = {{1, 1},
                 {1, 1}};
    Matrix m3 = {{1, 1},
                 {1, 1}};
    
    m1 += m2 += m3;
    
    EXPECT_DOUBLE_EQ(3.0, m1(0, 0));
    EXPECT_DOUBLE_EQ(2.0, m2(0, 0));
}

TEST(MatrixAddition, Associativity) {
    Matrix m1 = {{1, 2},
                 {3, 4}};
    Matrix m2 = {{5, 6},
                 {7, 8}};
    Matrix m3 = {{9, 10},
                 {11, 12}};
    
    Matrix result1 = (m1 + m2) + m3;
    Matrix result2 = m1 + (m2 + m3);
    
    EXPECT_EQ(result1, result2);
}

TEST(MatrixAddition, Commutativity) {
    Matrix m1 = {{1, 2},
                 {3, 4}};
    Matrix m2 = {{5, 6},
                 {7, 8}};
    
    Matrix result1 = m1 + m2;
    Matrix result2 = m2 + m1;
    
    EXPECT_EQ(result1, result2);
}

TEST(MatrixAddition, LargeMatrix) {
    Matrix m1 = Matrix::ones(100, 100);
    Matrix m2 = Matrix::ones(100, 100);
    Matrix result = m1 + m2;
    
    EXPECT_EQ(100, result.rows());
    EXPECT_EQ(100, result.cols());
    EXPECT_DOUBLE_EQ(2.0, result(0, 0));
    EXPECT_DOUBLE_EQ(2.0, result(99, 99));
}

// ========== STATIC FACTORY TESTS ==========

TEST(MatrixFactory, Identity) {
    Matrix I = Matrix::identity(3);
    EXPECT_EQ(3, I.rows());
    EXPECT_EQ(3, I.cols());
    
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (i == j) {
                EXPECT_DOUBLE_EQ(1.0, I(i, j));
            } else {
                EXPECT_DOUBLE_EQ(0.0, I(i, j));
            }
        }
    }
}

TEST(MatrixFactory, Zeros) {
    Matrix Z = Matrix::zeros(2, 3);
    EXPECT_EQ(2, Z.rows());
    EXPECT_EQ(3, Z.cols());
    
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_DOUBLE_EQ(0.0, Z(i, j));
        }
    }
}

TEST(MatrixFactory, Ones) {
    Matrix O = Matrix::ones(3, 2);
    EXPECT_EQ(3, O.rows());
    EXPECT_EQ(2, O.cols());
    
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            EXPECT_DOUBLE_EQ(1.0, O(i, j));
        }
    }
}

TEST(MatrixFactory, Diagonal) {
    std::vector<double> diag = {1, 2, 3};
    Matrix D = Matrix::diagonal(diag);
    
    EXPECT_EQ(3, D.rows());
    EXPECT_EQ(3, D.cols());
    EXPECT_DOUBLE_EQ(1.0, D(0, 0));
    EXPECT_DOUBLE_EQ(2.0, D(1, 1));
    EXPECT_DOUBLE_EQ(3.0, D(2, 2));
    EXPECT_DOUBLE_EQ(0.0, D(0, 1));
    EXPECT_DOUBLE_EQ(0.0, D(1, 0));
}

// ========== ELEMENT ACCESS TESTS ==========

TEST(MatrixAccess, OperatorAccess) {
    Matrix m(2, 2);
    m(0, 0) = 1.0;
    m(0, 1) = 2.0;
    m(1, 0) = 3.0;
    m(1, 1) = 4.0;
    
    EXPECT_DOUBLE_EQ(1.0, m(0, 0));
    EXPECT_DOUBLE_EQ(2.0, m(0, 1));
    EXPECT_DOUBLE_EQ(3.0, m(1, 0));
    EXPECT_DOUBLE_EQ(4.0, m(1, 1));
}

TEST(MatrixAccess, ConstAccess) {
    const Matrix m = {{1, 2},
                      {3, 4}};
    
    EXPECT_DOUBLE_EQ(1.0, m(0, 0));
    EXPECT_DOUBLE_EQ(4.0, m(1, 1));
}

TEST(MatrixAccess, AtMethodValid) {
    Matrix m = {{1, 2},
                {3, 4}};
    
    EXPECT_DOUBLE_EQ(1.0, m.at(0, 0));
    EXPECT_DOUBLE_EQ(4.0, m.at(1, 1));
}

TEST(MatrixAccess, AtMethodOutOfBounds) {
    Matrix m(2, 2);
    
    // Test row out of bounds
    bool threw1 = false;
    try {
        m.at(2, 0);
    } catch (const std::out_of_range&) {
        threw1 = true;
    }
    EXPECT_TRUE(threw1);
    
    // Test column out of bounds
    bool threw2 = false;
    try {
        m.at(0, 2);
    } catch (const std::out_of_range&) {
        threw2 = true;
    }
    EXPECT_TRUE(threw2);
    
    // Test both out of bounds
    bool threw3 = false;
    try {
        m.at(5, 5);
    } catch (const std::out_of_range&) {
        threw3 = true;
    }
    EXPECT_TRUE(threw3);
}

// ========== PROPERTY TESTS ==========

TEST(MatrixProperties, IsSquare) {
    Matrix m1(3, 3);
    Matrix m2(3, 4);
    Matrix m3(0, 0);
    
    EXPECT_TRUE(m1.isSquare());
    EXPECT_FALSE(m2.isSquare());
    EXPECT_FALSE(m3.isSquare());
}

TEST(MatrixProperties, IsEmpty) {
    Matrix m1;
    Matrix m2(2, 2);
    Matrix m3(0, 5);
    
    EXPECT_TRUE(m1.isEmpty());
    EXPECT_FALSE(m2.isEmpty());
    EXPECT_TRUE(m3.isEmpty());
}

// ========== COMPARISON TESTS ==========

TEST(MatrixComparison, Equality) {
    Matrix m1 = {{1, 2},
                 {3, 4}};
    Matrix m2 = {{1, 2},
                 {3, 4}};
    
    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 != m2);
}

TEST(MatrixComparison, InequalityValues) {
    Matrix m1 = {{1, 2},
                 {3, 4}};
    Matrix m2 = {{1, 2},
                 {3, 5}};
    
    EXPECT_TRUE(m1 != m2);
    EXPECT_FALSE(m1 == m2);
}

TEST(MatrixComparison, InequalitySize) {
    Matrix m1(2, 2);
    Matrix m2(3, 3);
    
    EXPECT_TRUE(m1 != m2);
    EXPECT_FALSE(m1 == m2);
}

TEST(MatrixComparison, EqualityWithEpsilon) {
    Matrix m1 = {{1.0, 2.0},
                 {3.0, 4.0}};
    Matrix m2 = {{1.0 + 1e-11, 2.0 + 1e-11},
                 {3.0 + 1e-11, 4.0 + 1e-11}};
    
    EXPECT_TRUE(m1 == m2);  // Should be equal within epsilon
}

// ========== MATRIX OPERATIONS TESTS ==========

TEST(MatrixOperations, Transpose) {
    Matrix m = {{1, 2, 3},
                {4, 5, 6}};
    Matrix t = m.transpose();
    
    EXPECT_EQ(3, t.rows());
    EXPECT_EQ(2, t.cols());
    EXPECT_DOUBLE_EQ(1.0, t(0, 0));
    EXPECT_DOUBLE_EQ(4.0, t(0, 1));
    EXPECT_DOUBLE_EQ(2.0, t(1, 0));
    EXPECT_DOUBLE_EQ(5.0, t(1, 1));
    EXPECT_DOUBLE_EQ(3.0, t(2, 0));
    EXPECT_DOUBLE_EQ(6.0, t(2, 1));
}

TEST(MatrixOperations, TransposeSquare) {
    Matrix m = {{1, 2},
                {3, 4}};
    Matrix t = m.transpose();
    
    EXPECT_EQ(2, t.rows());
    EXPECT_EQ(2, t.cols());
    EXPECT_DOUBLE_EQ(1.0, t(0, 0));
    EXPECT_DOUBLE_EQ(3.0, t(0, 1));
    EXPECT_DOUBLE_EQ(2.0, t(1, 0));
    EXPECT_DOUBLE_EQ(4.0, t(1, 1));
}

TEST(MatrixOperations, TransposeOfTranspose) {
    Matrix m = {{1, 2, 3},
                {4, 5, 6}};
    Matrix tt = m.transpose().transpose();
    
    EXPECT_EQ(m, tt);
}

TEST(MatrixOperations, TransposeRowVector) {
    Matrix m = {{1, 2, 3, 4}};
    Matrix t = m.transpose();
    
    EXPECT_EQ(4, t.rows());
    EXPECT_EQ(1, t.cols());
    EXPECT_DOUBLE_EQ(1.0, t(0, 0));
    EXPECT_DOUBLE_EQ(2.0, t(1, 0));
    EXPECT_DOUBLE_EQ(3.0, t(2, 0));
    EXPECT_DOUBLE_EQ(4.0, t(3, 0));
}

TEST(MatrixOperations, Trace) {
    Matrix m = {{1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}};
    double tr = m.trace();
    
    EXPECT_DOUBLE_EQ(15.0, tr);  // 1 + 5 + 9 = 15
}

TEST(MatrixOperations, TraceIdentity) {
    Matrix I = Matrix::identity(5);
    double tr = I.trace();
    
    EXPECT_DOUBLE_EQ(5.0, tr);
}

TEST(MatrixOperations, TraceNonSquare) {
    Matrix m(2, 3);
    bool threw = false;
    try {
        double tr = m.trace();
    } catch (const std::logic_error&) {
        threw = true;
    }
    EXPECT_TRUE(threw);
}

TEST(MatrixOperations, TraceSingleElement) {
    Matrix m = {{7}};
    EXPECT_DOUBLE_EQ(7.0, m.trace());
}

TEST(MatrixOperations, Diagonal) {
    Matrix m = {{1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}};
    Matrix diag = m.diagonal();
    
    EXPECT_EQ(3, diag.rows());
    EXPECT_EQ(1, diag.cols());
    EXPECT_DOUBLE_EQ(1.0, diag(0, 0));
    EXPECT_DOUBLE_EQ(5.0, diag(1, 0));
    EXPECT_DOUBLE_EQ(9.0, diag(2, 0));
}

TEST(MatrixOperations, DiagonalNonSquare) {
    Matrix m = {{1, 2, 3},
                {4, 5, 6}};
    Matrix diag = m.diagonal();
    
    EXPECT_EQ(2, diag.rows());
    EXPECT_EQ(1, diag.cols());
    EXPECT_DOUBLE_EQ(1.0, diag(0, 0));
    EXPECT_DOUBLE_EQ(5.0, diag(1, 0));
}

TEST(MatrixOperations, DiagonalSingleElement) {
    Matrix m = {{42}};
    Matrix diag = m.diagonal();
    
    EXPECT_EQ(1, diag.rows());
    EXPECT_EQ(1, diag.cols());
    EXPECT_DOUBLE_EQ(42.0, diag(0, 0));
}

TEST(MatrixOperations, Fill) {
    Matrix m(3, 4);
    m.fill(7.5);
    
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            EXPECT_DOUBLE_EQ(7.5, m(i, j));
        }
    }
}

TEST(MatrixOperations, FillOverwrite) {
    Matrix m = {{1, 2},
                {3, 4}};
    m.fill(0.0);
    
    EXPECT_DOUBLE_EQ(0.0, m(0, 0));
    EXPECT_DOUBLE_EQ(0.0, m(0, 1));
    EXPECT_DOUBLE_EQ(0.0, m(1, 0));
    EXPECT_DOUBLE_EQ(0.0, m(1, 1));
}

TEST(MatrixOperations, FillNegative) {
    Matrix m(2, 2);
    m.fill(-3.14);
    
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            EXPECT_DOUBLE_EQ(-3.14, m(i, j));
        }
    }
}

TEST(MatrixOperations, Norm) {
    Matrix m = {{1, 2},
                {3, 4}};
    double norm = m.norm();
    
    // sqrt(1^2 + 2^2 + 3^2 + 4^2) = sqrt(30)
    EXPECT_NEAR(std::sqrt(30.0), norm, 1e-9);
}

TEST(MatrixOperations, NormZeroMatrix) {
    Matrix m = Matrix::zeros(3, 3);
    EXPECT_DOUBLE_EQ(0.0, m.norm());
}

TEST(MatrixOperations, NormIdentity) {
    Matrix I = Matrix::identity(3);
    // sqrt(1 + 1 + 1) = sqrt(3)
    EXPECT_NEAR(std::sqrt(3.0), I.norm(), 1e-9);
}

TEST(MatrixOperations, NormSingleElement) {
    Matrix m = {{5}};
    EXPECT_DOUBLE_EQ(5.0, m.norm());
}

TEST(MatrixOperations, NormRowVector) {
    Matrix m = {{3, 4}};
    // sqrt(9 + 16) = 5
    EXPECT_DOUBLE_EQ(5.0, m.norm());
}

// ========== INTEGRATION TESTS ==========

TEST(MatrixIntegration, AdditionWithConstructors) {
    Matrix m1 = {{1, 2}, {3, 4}};
    Matrix m2(2, 2, 5.0);
    Matrix result = m1 + m2;
    
    EXPECT_DOUBLE_EQ(6.0, result(0, 0));
    EXPECT_DOUBLE_EQ(7.0, result(0, 1));
    EXPECT_DOUBLE_EQ(8.0, result(1, 0));
    EXPECT_DOUBLE_EQ(9.0, result(1, 1));
}

TEST(MatrixIntegration, MultipleAdditions) {
    Matrix m1 = {{1, 1}, {1, 1}};
    Matrix m2 = {{2, 2}, {2, 2}};
    Matrix m3 = {{3, 3}, {3, 3}};
    
    Matrix result = m1 + m2 + m3;
    
    EXPECT_DOUBLE_EQ(6.0, result(0, 0));
    EXPECT_DOUBLE_EQ(6.0, result(1, 1));
}

TEST(MatrixIntegration, TransposeAndNorm) {
    Matrix m = {{1, 2},
                {3, 4}};
    Matrix t = m.transpose();
    
    // Transpose should not change norm
    EXPECT_NEAR(m.norm(), t.norm(), 1e-9);
}

TEST(MatrixIntegration, FillAndTrace) {
    Matrix m(4, 4);
    m.fill(2.0);
    
    EXPECT_DOUBLE_EQ(8.0, m.trace());  // 2 * 4 = 8
}

TEST(MatrixIntegration, DiagonalAndTrace) {
    Matrix m = {{1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}};
    Matrix diag = m.diagonal();
    
    // Sum of diagonal vector should equal trace
    double sum = 0.0;
    for (size_t i = 0; i < diag.rows(); ++i) {
        sum += diag(i, 0);
    }
    EXPECT_DOUBLE_EQ(m.trace(), sum);
}

}  // namespace