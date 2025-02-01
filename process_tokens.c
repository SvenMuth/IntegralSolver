//
// Created by sven on 30.01.25.
//

#include <stdlib.h>
#include <string.h>

#include "process_tokens.h"
#include "commons.h"
#include "math.h"

void clear_char_buffer(char* buffer)
{
    memset(&buffer[0], '0', sizeof(buffer));
    buffer[3] = '\0';
}

void construct_number_buffer(char* buffer, char number, int digit)
{
    if (digit == 1)
    {
        buffer[2] = number;
    }
    if (digit == 2)
    {
        buffer[1] = buffer[2];
        buffer[2] = number;
    }
    if (digit == 3)
    {
        buffer[0] = buffer[1];
        buffer[1] = buffer[2];
        buffer[2] = number;
    }
}

void strip_numbers_token(token_t* tokens, token_t* token_with_placeholders, double* numbers)
{
    int index = 0;

    char buffer[4];
    clear_char_buffer(buffer);

    int numbers_index = 0;

    for (int i = 0; i < SIZE_TOKENS; i++)
    {
        if (tokens[i].type == NUMBER)
        {
            int digit = 1;
            int tmp = i;

            while (check_is_token_number(tokens, tmp))
            {
                construct_number_buffer(buffer, tokens[tmp].token_c, digit);
                digit++;
                tmp++;
            }

            i = tmp - 1;

            numbers[numbers_index] = (int)strtol(buffer, nullptr, 10);
            numbers_index++;

            token_with_placeholders[index] = (token_t){'%', PLACEHOLDER_NUMBER};
            index++;

            clear_char_buffer(buffer);
            continue;
        }

        token_with_placeholders[index] = tokens[i];
        index++;
    }

    printf("\n\n");
    print_tokens(token_with_placeholders);
}

void execute_tokens(token_t* tokens, double* numbers, double* result, double* x)
{
    int parenthese_level = 0;
    int numbers_index = 0;

    bool is_mul_or_div = false;

    for (int i = 0; i < 4; i++)
    {
        printf("%f\n", numbers[i]);
    }

    *result = numbers[numbers_index];
    numbers_index++;

    for (int i = 0; i < SIZE_TOKENS; i++)
    {
        const char token_c = tokens[i].token_c;
        const type_t type = tokens[i].type;

        if (type == UNINITIALIZED)
        {
            break;
        }

        if (type == PARENTHESE_OPEN)
        {
            printf("PARENTHESE_OPEN\n");
            parenthese_level++;
            continue;
        }

        if (type == PARENTHESE_CLOSE)
        {
            printf("PARENTHESE_CLOSE\n");
            parenthese_level--;
            continue;
        }

        if (type == VARIABLE)
        {
            printf("VARIABLE\n");
        }

        if (tokens[i + 2].type  == POWER)
        {
            printf("POWER\n");
            //3 + 4 ^ 2 + 2
            numbers[numbers_index + 1] = power(numbers[numbers_index], (int)numbers[numbers_index + 1]);
            numbers_index++;
        }

        if (type == ADDITION || type == SUBTRACTION)
        {
            int counter_mul_or_div = 0;
            // 3 + 4 * 4 * 3 + 2
            int tmp = i + 2;
            while (check_is_token_mul(tokens, tmp))
            {
                printf("MULTIPLICATION\n");
                numbers[numbers_index] = multiply(numbers[numbers_index], numbers[numbers_index + 1]);
                is_mul_or_div = true;
                counter_mul_or_div++;
                tmp += 2;
            }
            while (check_is_token_div(tokens, tmp))
            {
                printf("DIVISION\n");
                numbers[numbers_index] = divide(numbers[numbers_index], numbers[numbers_index + 1]);
                is_mul_or_div = true;
                counter_mul_or_div++;
                tmp += 2;
            }

            i = tmp - 2;

            if (type == ADDITION)
            {
                printf("ADDITION\n");
                *result = add(*result, numbers[numbers_index]);
                numbers_index++;
            }
            if (type == SUBTRACTION)
            {
                printf("SUBTRACTION\n");
                *result = subtract(*result, numbers[numbers_index]);
                numbers_index++;
            }

            if (is_mul_or_div)
            {
                numbers_index += counter_mul_or_div;
            }
        }

        if (type == MULTIPLICATION)
        {
            printf("MULTIPLICATION\n");
            *result = multiply(*result, numbers[numbers_index]);
            numbers_index++;
        }
        if (type == DIVISION)
        {
            printf("DIVISION\n");
            *result = divide(*result, numbers[numbers_index]);
            numbers_index++;
        }
    }
}

bool check_is_token_mul(token_t* tokens, const int index)
{
    type_t next_token = UNINITIALIZED;
    if (index < SIZE_TOKENS)
    {
        next_token = tokens[index].type;
    }

    if (next_token == MULTIPLICATION)
    {
        return true;
    }

    return false;
}

bool check_is_token_div(token_t* tokens, const int index)
{
    type_t next_token = UNINITIALIZED;
    if (index < SIZE_TOKENS)
    {
        next_token = tokens[index].type;
    }

    if (next_token == DIVISION)
    {
        return true;
    }

    return false;
}

bool check_is_token_number(token_t* tokens, const int index)
{
    type_t next_token = UNINITIALIZED;
    if (index < SIZE_TOKENS)
    {
        next_token = tokens[index].type;
    }

    if (next_token == NUMBER)
    {
        return true;
    }

    return false;
}

bool check_is_token_power(token_t* tokens, const int index)
{
    type_t next_token = UNINITIALIZED;
    if (index < SIZE_TOKENS)
    {
        next_token = tokens[index].type;
    }

    if (next_token == POWER)
    {
        return true;
    }

    return false;
}
