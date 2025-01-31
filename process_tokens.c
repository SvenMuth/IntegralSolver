//
// Created by sven on 30.01.25.
//

#include <stdlib.h>
#include <string.h>

#include "process_tokens.h"
#include "commons.h"

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

void strip_numbers_token(token_t* tokens)
{
    token_t* token_with_placeholders = default_initialization_tokens();
    int index = 0;

    char buffer[4];
    clear_char_buffer(buffer);

    for (int i = 0; i < SIZE_TOKENS; i++)
    {
        if (tokens[i].type == NUMBER)
        {

            int digit = 1;
            int tmp = i + 1;
            construct_number_buffer(buffer, tokens[i].token_c, digit);
            while (check_is_token_number(tokens, tmp))
            {
                digit++;
                construct_number_buffer(buffer, tokens[tmp].token_c, digit);
                tmp++;
            }

            i = tmp;
            const int number = (int)strtol(buffer, nullptr, 10);
            printf("%d\n", number);

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

void execute_tokens(const token_t* tokens)
{
    int parenthese_level = 0;

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
