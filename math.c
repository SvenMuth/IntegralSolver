//
// Created by sven on 30.01.25.
//

#include <math.h>
#include <assert.h>
#include <stdlib.h>

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

//need double here as exponent? Base as double works
double power(double base, int exponent)
{
    if (exponent == 0)
    {
        return 1;
    }
    if (exponent == 1)
    {
        return base;
    }

    while (true)
    {
        base *= base;
        if (exponent == 2)
        {
            break;
        }
        exponent--;
    }

    return base;
}

/*
unsigned int mul_div_by_two(const unsigned int base, unsigned int bit)
{
    if (bit == 0)
    {
        ERROR_PRINT("bit can not be 0");
        exit(EXIT_FAILURE);
    }
    bit--;
    return base << bit;
}
*/

























