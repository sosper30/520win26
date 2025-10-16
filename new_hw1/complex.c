#include "complex.h"
#include <math.h>

#define EPSILON 1e-9

struct complex add(struct complex a, struct complex b) {
    struct complex result;
    result.real = a.real + b.real;
    result.im = a.im + b.im;
    return result;
}

struct complex subtract(struct complex a, struct complex b) {
    struct complex result;
    result.real = a.real - b.real;
    result.im = a.im - b.im;
    return result;
}

struct complex negate(struct complex a) {
    struct complex result;
    result.real = -a.real;
    result.im = -a.im;
    return result;
}

struct complex multiply(struct complex a, struct complex b) {
    struct complex result;
    result.real = a.real * b.real - a.im * b.im;
    result.im = a.real * b.im + a.im * b.real;
    return result;
}

struct complex divide(struct complex a, struct complex b) {
    struct complex result;
    double denominator = b.real * b.real + b.im * b.im;
    
    // Check for division by zero
    if (fabs(denominator) < EPSILON) {
        result.real = INFINITY;
        result.im = INFINITY;
        return result;
    }
    
    result.real = (a.real * b.real + a.im * b.im) / denominator;
    result.im = (a.im * b.real - a.real * b.im) / denominator;
    return result;
}

struct complex conjugate(struct complex a) {
    struct complex result;
    result.real = a.real;
    result.im = -a.im;
    return result;
}

struct polar to_polar(struct complex a) {
    struct polar result;
    result.r = sqrt(a.real * a.real + a.im * a.im);
    result.theta = atan2(a.im, a.real);
    return result;
}

struct complex power(struct complex a, int n) {
    // Handle special cases
    if (n == 0) {
        struct complex result = {1.0, 0.0};
        return result;
    }
    
    if (n < 0) {
        // For negative powers, compute 1/a^|n|
        struct complex one = {1.0, 0.0};
        struct complex positive_power = power(a, -n);
        return divide(one, positive_power);
    }
    
    // Use repeated squaring for efficiency
    struct complex result = {1.0, 0.0};
    struct complex base = a;
    
    while (n > 0) {
        if (n % 2 == 1) {
            result = multiply(result, base);
        }
        base = multiply(base, base);
        n /= 2;
    }
    
    return result;
}

double magnitude(struct complex a) {
    return sqrt(a.real * a.real + a.im * a.im);
}

int equals(struct complex a, struct complex b) {
    return (fabs(a.real - b.real) < EPSILON) && 
           (fabs(a.im - b.im) < EPSILON);
}

int is_real(struct complex a) {
    return fabs(a.im) < EPSILON;
}

int is_imaginary(struct complex a) {
    return (fabs(a.real) < EPSILON) && (fabs(a.im) >= EPSILON);
}

int is_zero(struct complex a) {
    return (fabs(a.real) < EPSILON) && (fabs(a.im) < EPSILON);
}