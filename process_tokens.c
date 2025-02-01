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
        buffer[0] = buffer[1] ;
        buffer[1] = buffer[2] ;
        buffer[2] = number;
    }
}

void strip_numbers_token(token_t* tokens, token_t* token_with_placeholders, int* numbers)
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

void execute_tokens(token_t* tokens, const int* numbers, double* result, double* x)
{
    int parenthese_level = 0;
    int numbers_index = 0;

    //double number_placeholder_left = 0;
    //bool is_placeholder_left = false;

    //double number_placeholder_right = 0;
    //bool is_placeholder_right = false;

    bool is_variable_and_power = false;

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
            parenthese_level++;
            continue;
        }

        if (type == PARENTHESE_CLOSE)
        {
            parenthese_level--;
            break;
        }

        if (type == VARIABLE)
        {
            if (check_is_token_power(tokens, i + 1))
            {
                is_variable_and_power = true;
            }
            //3x
            //4 + 3x
            //4 + 3x - 5
            //if (is_placeholder_left)
            //{

            //}
            //if (is_placeholder_right)
            //{

            //}
        }

        //if (type == POWER)
        //{
        //    is_power = true;
        //    continue;
        //}

        if (type == PLACEHOLDER_NUMBER)
        {
            if (!is_placeholder_left)
            {
                number_placeholder_left = numbers[numbers_index];
                is_placeholder_left = true;
                numbers_index++;
                continue;
            }
            if (!is_placeholder_right)
            {
                number_placeholder_right = numbers[numbers_index];
                is_placeholder_right = true;
                numbers_index++;
                continue;
            }
        }


        //if (is_power)
        //{
        //    power(number_placeholder_left, (int)number_placeholder_right);
        //}

        if (type == ADDITION || type == SUBTRACTION)
        {
            if (!is_placeholder_right)
            {
                number_placeholder_right = numbers[numbers_index];
                numbers_index++;
            }
            //5 + 3 * 2
            //5 + 3 + 2
            if (type == ADDITION)
            {
                *result = add(number_placeholder_left ,number_placeholder_right);
            }
            if (type == SUBTRACTION)
            {
                *result = subtract(number_placeholder_left ,number_placeholder_right);
            }
        }
        if (type == MULTIPLICATION)
        {
            *result = multiply(number_placeholder_left, number_placeholder_right);
        }
        if (type == DIVISION)
        {
            *result = divide(number_placeholder_left, number_placeholder_right);
        }

        //if (is_power)
        //{
        //    number_placeholder_left = *result;
        //    is_placeholder_right = false;
        //    is_power = false;
        //}

        if (type == ADDITION || type == SUBTRACTION || type == MULTIPLICATION || type == DIVISION)
        {
            number_placeholder_left = *result;
            is_placeholder_right = false;
        }
    }
}

bool check_is_token_mul_or_div(token_t* tokens, const int index)
{
    type_t next_token = UNINITIALIZED;
    if (index < SIZE_TOKENS)
    {
        next_token = tokens[index].type;
    }

    if (next_token == MULTIPLICATION || next_token == DIVISION)
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
