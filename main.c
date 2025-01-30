#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "main.h"
#include "math.h"


static double x = 0;

void generate_token(token_t* token, type_t type, const char content)
{
    *token = (token_t) {
        .token_c = content,
        .type = type,
    };
}

void print_tokens(const token_t* tokens)
{
    for (int i = 0; i < SIZE_TOKENS; i++)
    {
        if (tokens[i].type == UNINITIALIZED)
        {
            break;
        }

        printf("content: %c     type: %d\n",
            tokens[i].token_c, tokens[i].type);
    }
}

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


int main(void)
{
    const char* integral = "x ^ 3 + 2 x ^ 2 - 4 x + 5";

    token_t* tokens = malloc(sizeof(token_t) * SIZE_TOKENS);
    if (tokens == nullptr)
    {
        ERROR_PRINT("Memory allocation failed!");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < SIZE_TOKENS; i++)
    {
        tokens[i] = (token_t){
            .token_c = '0',
            .type = UNINITIALIZED
        };
    }

    int token_index = 0;
    type_t type = UNINITIALIZED;

    for (int i = 0; i < strlen(integral); i++)
    {
        char c = integral[i];
        if (isspace(c) || iscntrl(c))
        {
            continue;
        }

        if (isdigit(c))
        {
            type = NUMBER;
        }

        if (isalpha(c))
        {
            type = VARIABLE;
            if (isupper(c))
            {
                c = (char)tolower(c);
            }
        }

        switch (c)
        {
        case MULTIPLICATION:    type = MULTIPLICATION;      break;
        case DIVISION:          type = DIVISION;            break;
        case ADDITION:          type = ADDITION;            break;
        case SUBTRACTION:       type = SUBTRACTION;         break;
        case POWER:             type = POWER;               break;
        case PARENTHESE_OPEN:   type = PARENTHESE_OPEN;     break;
        case PARENTHESE_CLOSE:  type = PARENTHESE_CLOSE;    break;
        default: break;
        }

        generate_token(&tokens[token_index], type, c);
        token_index++;
    }

    print_tokens(tokens);
    translate_into_formula(tokens);

    power(2, 4);

    free(tokens);
    return EXIT_SUCCESS;
}























