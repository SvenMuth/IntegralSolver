//
// Created by sven on 30.01.25.
//

#include "process_tokens.h"

#include <stdlib.h>

//Need to check left side?
bool check_left_token_mul_or_div(const token_t* tokens, const int index)
{
    type_t type_left = UNINITIALIZED;
    if (index - 1 >= 0)
    {
        type_left = tokens[index - 1].type;
    }

    if (type_left == MULTIPLICATION || type_left == DIVISION)
    {
        return true;
    }

    return false;
}

bool check_next_token_mul_or_div(const token_t* tokens, const int index)
{
    type_t next_token = UNINITIALIZED;
    if (index + 1 < SIZE_TOKENS)
    {
        next_token = tokens[index + 1].type;
    }

    if (next_token == MULTIPLICATION || next_token == DIVISION)
    {
        return true;
    }

    return false;
}

//Need to check left side?
bool check_left_token_number(const token_t* tokens, const int index)
{
    type_t type_left = UNINITIALIZED;
    if (index + 1 < SIZE_TOKENS)
    {
        type_left = tokens[index + 1].type;
    } //Needs case if index+1 > SIZE_TOKENS

    if (type_left == NUMBER)
    {
        return true;
    }

    return false;
}

bool check_next_token_number(const token_t* tokens, const int index)
{
    type_t next_token = UNINITIALIZED;
    if (index + 1 < SIZE_TOKENS)
    {
        next_token = tokens[index + 1].type;
    }

    if (next_token == NUMBER)
    {
        return true;
    }

    return false;
}

void construct_number_with_multiple_digits(section_t* section, const type_t type, const char number_c)
{
    if (section->token_arr == nullptr)
    {
        section->size = 1;
        *section = (section_t) {
            .token_arr = malloc(sizeof(token_t) * section->size),
            .size = section->size + 1,
            .type = type,
        };
    }
    else
    {
        section->token_arr = realloc(section->token_arr, sizeof(token_t) * section->size);
        section->token_arr[section->size - 1] = number_c;
        section->size += 1;
    }
}

void translate_into_formula(const token_t* tokens)
{
    token_t* token_buffer = malloc(sizeof(token_t) * 10);
    int token_buffer_index = 0;
    bool parentheses = false;

    static section_t* section = nullptr;

    for (int i = 0; i < SIZE_TOKENS; i++)
    {
        const char token_c = tokens[i].token_c;
        const type_t type = tokens[i].type;

        if (type == PARENTHESE_CLOSE)
        {
            parentheses = false;
            break;
        }

        if (parentheses)
        {
            token_buffer[token_buffer_index] = tokens[i];
            token_buffer_index++;
        }

        if (type == UNINITIALIZED) break;
        if (type == PARENTHESE_OPEN)
        {
            parentheses = true;
            continue;
        }

        if (type == NUMBER)
        {
            if (check_left_token_number(tokens, i))
            {
                construct_number_with_multiple_digits(section, type, token_c);
            }
            if (check_next_token_number(tokens, i))
            {
                construct_number_with_multiple_digits(section, type, token_c);
            }
        }

        if (type == ADDITION || type == SUBTRACTION)
        {
            if (check_left_token_mul_or_div(tokens, i))
            {

            }
            if (check_next_token_mul_or_div(tokens, i))
            {

            }
        }
        if (type == MULTIPLICATION)
        {

        }
        if (type == DIVISION)
        {

        }
    }

    free(token_buffer);
}