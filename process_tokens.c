//
// Created by sven on 30.01.25.
//

#include <stdlib.h>

#include "process_tokens.h"
#include "commons.h"


void strip_numbers_token(token_t* tokens)
{
    token_t* token_with_placeholders = default_initialization_tokens();
    int index = 0;

    int tmp = -1;
    int digits = 1;
    char* buffer = nullptr;
    for (int i = 0; i < SIZE_TOKENS; i++)
    {
        if (tokens[i].type == NUMBER)
        {
            int index_buffer = 0;
            digits = 1;

            buffer = malloc(sizeof(char) * digits);
            buffer[index_buffer] = tokens[i].token_c;

            tmp = i + 1;
            while (check_is_token_number(tokens, tmp))
            {
                index_buffer++;
                digits++;

                buffer = realloc(buffer, sizeof(char) * digits);
                buffer[index_buffer] = tokens[tmp].token_c;
                tmp++;
            }

            i = tmp + 1;

            digits++;
            index_buffer++;
            buffer = realloc(buffer, sizeof(char) * digits);
            buffer[index_buffer] = 0;
            int number = (int)strtol(buffer, nullptr, 10);

            token_with_placeholders[index] = (token_t){'%', PLACEHOLDER_NUMBER};
            index++;
            continue;
        }
        token_with_placeholders[index] = tokens[i];
        index++;
    }

    printf("\n\n");
    print_tokens(token_with_placeholders);

    free(buffer);
}

void execute_tokens(const token_t* tokens)
{
    int parenthese_level = 0;

    char number_buffer[] = "000";
    int index_number_buffer = 2;

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

        if (type == PLACEHOLDER_NUMBER)
        {
        }

        if (type == ADDITION || type == SUBTRACTION)
        {
            if (check_is_token_mul_or_div(tokens, i))
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
}

bool check_is_token_mul_or_div(const token_t* tokens, const int index)
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


bool check_is_token_number(const token_t* tokens, const int index)
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
