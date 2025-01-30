//
// Created by sven on 30.01.25.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tokenizer.h"
#include "commons.h"

token_t* tokenize(const char* integral)
{
    token_t* tokens = malloc(sizeof(token_t) * SIZE_TOKENS);
    if (tokens == nullptr)
    {
        ERROR_PRINT("Memory allocation failed!");
        exit(EXIT_FAILURE);
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

    return tokens;
}

void generate_token(token_t* token, type_t type, const char content)
{
    *token = (token_t) {
        .token_c = content,
        .type = type,
    };
}

void print_tokens(const token_t* tokens)
{
    char* type_str = nullptr;
    type_t type = UNINITIALIZED;
    for (int i = 0; i < SIZE_TOKENS; i++)
    {
        type = tokens[i].type;
        if (type == UNINITIALIZED)
        {
            break;
        }

        switch (type)
        {
        case NUMBER:            type_str = "NUMBER";            break;
        case VARIABLE:          type_str = "VARIABLE";          break;
        case EXPONENT:          type_str = "EXPONENT";          break;
        case MULTIPLICATION:    type_str = "MULTIPLICATION";    break;
        case DIVISION:          type_str = "DIVISION";          break;
        case ADDITION:          type_str = "ADDITION";          break;
        case SUBTRACTION:       type_str = "SUBTRACTION";       break;
        case POWER:             type_str = "POWER";             break;
        case PARENTHESE_OPEN:   type_str = "PARENTHESE_OPEN";   break;
        case PARENTHESE_CLOSE:  type_str = "PARENTHESE_CLOSE";  break;
        default: break;
        }

        printf("content: %c\ttype: %s\n",
            tokens[i].token_c, type_str);
    }
}

















