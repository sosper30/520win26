#include "complex.h"
#include "gtest/gtest.h"
#include <cmath>

namespace {
    // ========== ADD TESTS ==========
    TEST(Complex, AddBasic) {
        struct complex a = (struct complex) { 3.0, 4.0 },
                       b = (struct complex) { 1.0, 2.0 };
        EXPECT_EQ(add(a, b).real, 4.0);
        EXPECT_EQ(add(a, b).im, 6.0);
    }

    TEST(Complex, AddNegative) {
        struct complex a = (struct complex) { 5.0, -3.0 },
                       b = (struct complex) { -2.0, 7.0 };
        EXPECT_EQ(add(a, b).real, 3.0);
        EXPECT_EQ(add(a, b).im, 4.0);
    }

    TEST(Complex, AddZero) {
        struct complex a = (struct complex) { 3.0, 4.0 },
                       b = (struct complex) { 0.0, 0.0 };
        EXPECT_EQ(add(a, b).real, 3.0);
        EXPECT_EQ(add(a, b).im, 4.0);
    }

    // ========== SUBTRACT TESTS ==========
    TEST(Complex, SubtractBasic) {
        struct complex a = (struct complex) { 5.0, 7.0 },
                       b = (struct complex) { 2.0, 3.0 };
        EXPECT_EQ(subtract(a, b).real, 3.0);
        EXPECT_EQ(subtract(a, b).im, 4.0);
    }

    TEST(Complex, SubtractNegative) {
        struct complex a = (struct complex) { 3.0, 4.0 },
                       b = (struct complex) { -1.0, -2.0 };
        EXPECT_EQ(subtract(a, b).real, 4.0);
        EXPECT_EQ(subtract(a, b).im, 6.0);
    }

    TEST(Complex, SubtractSelf) {
        struct complex a = (struct complex) { 3.0, 4.0 };
        struct complex result = subtract(a, a);
        EXPECT_EQ(result.real, 0.0);
        EXPECT_EQ(result.im, 0.0);
    }

    // ========== NEGATE TESTS ==========
    TEST(Complex, NegatePositive) {
        struct complex a = (struct complex) { 3.0, 4.0 };
        EXPECT_EQ(negate(a).real, -3.0);
        EXPECT_EQ(negate(a).im, -4.0);
    }

    TEST(Complex, NegateNegative) {
        struct complex a = (struct complex) { -5.0, -2.0 };
        EXPECT_EQ(negate(a).real, 5.0);
        EXPECT_EQ(negate(a).im, 2.0);
    }

    TEST(Complex, NegateZero) {
        struct complex a = (struct complex) { 0.0, 0.0 };
        EXPECT_EQ(negate(a).real, 0.0);
        EXPECT_EQ(negate(a).im, 0.0);
    }

    // ========== MULTIPLY TESTS ==========
    TEST(Complex, MultiplyBasic) {
        struct complex a = (struct complex) { 3.0, 2.0 },
                       b = (struct complex) { 1.0, 4.0 };
        // (3+2i)(1+4i) = 3 + 12i + 2i + 8i^2 = -5 + 14i
        EXPECT_EQ(multiply(a, b).real, -5.0);
        EXPECT_EQ(multiply(a, b).im, 14.0);
    }

    TEST(Complex, MultiplyByI) {
        struct complex a = (struct complex) { 1.0, 0.0 },
                       i = (struct complex) { 0.0, 1.0 };
        EXPECT_EQ(multiply(a, i).real, 0.0);
        EXPECT_EQ(multiply(a, i).im, 1.0);
    }

    TEST(Complex, MultiplyByZero) {
        struct complex a = (struct complex) { 3.0, 4.0 },
                       b = (struct complex) { 0.0, 0.0 };
        EXPECT_EQ(multiply(a, b).real, 0.0);
        EXPECT_EQ(multiply(a, b).im, 0.0);
    }

    // ========== DIVIDE TESTS ==========
    TEST(Complex, DivideBasic) {
        struct complex a = (struct complex) { 10.0, 5.0 },
                       b = (struct complex) { 2.0, 1.0 };
        // (10+5i)/(2+i) = (10+5i)(2-i)/(5) = (20-10i+10i-5i²)/5 = (25)/5 = 5
        EXPECT_DOUBLE_EQ(divide(a, b).real, 5.0);
        EXPECT_DOUBLE_EQ(divide(a, b).im, 0.0);
    }

    TEST(Complex, DivideByI) {
        struct complex a = (struct complex) { 0.0, 1.0 },
                       i = (struct complex) { 0.0, 1.0 };
        // i/i = 1
        EXPECT_DOUBLE_EQ(divide(a, i).real, 1.0);
        EXPECT_DOUBLE_EQ(divide(a, i).im, 0.0);
    }

    TEST(Complex, DivideByReal) {
        struct complex a = (struct complex) { 6.0, 8.0 },
                       b = (struct complex) { 2.0, 0.0 };
        EXPECT_DOUBLE_EQ(divide(a, b).real, 3.0);
        EXPECT_DOUBLE_EQ(divide(a, b).im, 4.0);
    }

    TEST(Complex, DivideByZero) {
        struct complex a = (struct complex) { 3.0, 4.0 },
                       b = (struct complex) { 0.0, 0.0 };
        struct complex result = divide(a, b);
        EXPECT_TRUE(std::isinf(result.real));
        EXPECT_TRUE(std::isinf(result.im));
    }

    // ========== CONJUGATE TESTS ==========
    TEST(Complex, ConjugatePositive) {
        struct complex a = (struct complex) { 3.0, 4.0 };
        EXPECT_EQ(conjugate(a).real, 3.0);
        EXPECT_EQ(conjugate(a).im, -4.0);
    }

    TEST(Complex, ConjugateNegative) {
        struct complex a = (struct complex) { 5.0, -7.0 };
        EXPECT_EQ(conjugate(a).real, 5.0);
        EXPECT_EQ(conjugate(a).im, 7.0);
    }

    TEST(Complex, ConjugateReal) {
        struct complex a = (struct complex) { 5.0, 0.0 };
        EXPECT_EQ(conjugate(a).real, 5.0);
        EXPECT_EQ(conjugate(a).im, 0.0);
    }

    // ========== POLAR TESTS ==========
    TEST(Complex, ToPolar345) {
        struct complex a = (struct complex) { 3.0, 4.0 };
        struct polar p = to_polar(a);
        EXPECT_DOUBLE_EQ(p.r, 5.0);
        EXPECT_DOUBLE_EQ(p.theta, atan2(4.0, 3.0));
    }

    TEST(Complex, ToPolarReal) {
        struct complex a = (struct complex) { 5.0, 0.0 };
        struct polar p = to_polar(a);
        EXPECT_DOUBLE_EQ(p.r, 5.0);
        EXPECT_DOUBLE_EQ(p.theta, 0.0);
    }

    TEST(Complex, ToPolarImaginary) {
        struct complex a = (struct complex) { 0.0, 5.0 };
        struct polar p = to_polar(a);
        EXPECT_DOUBLE_EQ(p.r, 5.0);
        EXPECT_DOUBLE_EQ(p.theta, M_PI / 2.0);
    }

    TEST(Complex, ToPolarNegativeReal) {
        struct complex a = (struct complex) { -5.0, 0.0 };
        struct polar p = to_polar(a);
        EXPECT_DOUBLE_EQ(p.r, 5.0);
        EXPECT_DOUBLE_EQ(p.theta, M_PI);
    }

    // ========== POWER TESTS ==========
    TEST(Complex, PowerZero) {
        struct complex a = (struct complex) { 3.0, 4.0 };
        struct complex result = power(a, 0);
        EXPECT_DOUBLE_EQ(result.real, 1.0);
        EXPECT_DOUBLE_EQ(result.im, 0.0);
    }

    TEST(Complex, PowerOne) {
        struct complex a = (struct complex) { 3.0, 4.0 };
        struct complex result = power(a, 1);
        EXPECT_DOUBLE_EQ(result.real, 3.0);
        EXPECT_DOUBLE_EQ(result.im, 4.0);
    }

    TEST(Complex, PowerTwo) {
        struct complex a = (struct complex) { 1.0, 1.0 };
        struct complex result = power(a, 2);
        // (1+i)² = 1 + 2i + i² = 1 + 2i - 1 = 2i
        EXPECT_DOUBLE_EQ(result.real, 0.0);
        EXPECT_DOUBLE_EQ(result.im, 2.0);
    }

    TEST(Complex, PowerThree) {
        struct complex i = (struct complex) { 0.0, 1.0 };
        struct complex result = power(i, 3);
        // i³ = -i
        EXPECT_NEAR(result.real, 0.0, 1e-9);
        EXPECT_DOUBLE_EQ(result.im, -1.0);
    }

    TEST(Complex, PowerNegative) {
        struct complex i = (struct complex) { 0.0, 1.0 };
        struct complex result = power(i, -1);
        // 1/i = -i
        EXPECT_NEAR(result.real, 0.0, 1e-9);
        EXPECT_DOUBLE_EQ(result.im, -1.0);
    }

    // ========== MAGNITUDE TESTS ==========
    TEST(Complex, Magnitude345) {
        struct complex a = (struct complex) { 3.0, 4.0 };
        EXPECT_DOUBLE_EQ(magnitude(a), 5.0);
    }

    TEST(Complex, MagnitudeZero) {
        struct complex a = (struct complex) { 0.0, 0.0 };
        EXPECT_DOUBLE_EQ(magnitude(a), 0.0);
    }

    TEST(Complex, MagnitudeReal) {
        struct complex a = (struct complex) { 5.0, 0.0 };
        EXPECT_DOUBLE_EQ(magnitude(a), 5.0);
    }

    TEST(Complex, MagnitudeImaginary) {
        struct complex a = (struct complex) { 0.0, 5.0 };
        EXPECT_DOUBLE_EQ(magnitude(a), 5.0);
    }

    // ========== EQUALS TESTS ==========
    TEST(Complex, EqualsTrue) {
        struct complex a = (struct complex) { 3.0, 4.0 },
                       b = (struct complex) { 3.0, 4.0 };
        EXPECT_EQ(equals(a, b), 1);
    }

    TEST(Complex, EqualsFalse) {
        struct complex a = (struct complex) { 3.0, 4.0 },
                       b = (struct complex) { 3.0, 5.0 };
        EXPECT_EQ(equals(a, b), 0);
    }

    TEST(Complex, EqualsWithEpsilon) {
        struct complex a = (struct complex) { 3.0, 4.0 },
                       b = (struct complex) { 3.0 + 1e-10, 4.0 };
        EXPECT_EQ(equals(a, b), 1);
    }

    // ========== IS_REAL TESTS ==========
    TEST(Complex, IsRealTrue) {
        struct complex a = (struct complex) { 5.0, 0.0 };
        EXPECT_EQ(is_real(a), 1);
    }

    TEST(Complex, IsRealFalse) {
        struct complex a = (struct complex) { 5.0, 0.1 };
        EXPECT_EQ(is_real(a), 0);
    }

    TEST(Complex, IsRealZero) {
        struct complex a = (struct complex) { 0.0, 0.0 };
        EXPECT_EQ(is_real(a), 1);  // Zero is considered real
    }

    TEST(Complex, IsRealWithEpsilon) {
        struct complex a = (struct complex) { 5.0, 1e-10 };
        EXPECT_EQ(is_real(a), 1);
    }

    // ========== IS_IMAGINARY TESTS ==========
    TEST(Complex, IsImaginaryTrue) {
        struct complex a = (struct complex) { 0.0, 5.0 };
        EXPECT_EQ(is_imaginary(a), 1);
    }

    TEST(Complex, IsImaginaryFalse) {
        struct complex a = (struct complex) { 0.1, 5.0 };
        EXPECT_EQ(is_imaginary(a), 0);
    }

    TEST(Complex, IsImaginaryZero) {
        struct complex a = (struct complex) { 0.0, 0.0 };
        EXPECT_EQ(is_imaginary(a), 0);  // Zero is not considered purely imaginary
    }

    TEST(Complex, IsImaginaryWithEpsilon) {
        struct complex a = (struct complex) { 1e-10, 5.0 };
        EXPECT_EQ(is_imaginary(a), 1);
    }

    // ========== IS_ZERO TESTS ==========
    TEST(Complex, IsZeroTrue) {
        struct complex a = (struct complex) { 0.0, 0.0 };
        EXPECT_EQ(is_zero(a), 1);
    }

    TEST(Complex, IsZeroFalse) {
        struct complex a = (struct complex) { 0.1, 0.0 };
        EXPECT_EQ(is_zero(a), 0);
    }

    TEST(Complex, IsZeroWithEpsilon) {
        struct complex a = (struct complex) { 1e-10, 1e-10 };
        EXPECT_EQ(is_zero(a), 1);
    }
}