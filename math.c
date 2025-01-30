//
// Created by sven on 30.01.25.
//

#include <math.h>
#include <assert.h>

#include "math.h"

double add(const double a, const double b)
{
    return a + b;
}

double subtract(const double a, const double b)
{
    return a - b;
}

double multiply(const double a, const double b)
{
    return a * b;
}

double divide(const double a, const double b)
{
    return a / b;
}

double power(double base, double exponent)
{
    while (exponent > 1)
    {
        base *= base;
        exponent--;
    }
    assert(base == pow(base, exponent));
    return base;
}
