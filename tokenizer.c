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

token_t* default_initialization_tokens()
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

    return tokens;
}

token_t* tokenize(const char* integral)
{
    token_t* tokens = default_initialization_tokens();

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

        set_token(&tokens[token_index], type, c);
        token_index++;
    }

    print_tokens(tokens);

    return tokens;
}

void set_token(token_t* token, type_t type, const char content)
{
    token->token_c = content;
    token->type= type;
}

void print_tokens(const token_t* tokens)
{
    type_t type = UNINITIALIZED;
    for (int i = 0; i < SIZE_TOKENS; i++)
    {
        static char type_str[20];

        type = tokens[i].type;
        if (type == UNINITIALIZED)
        {
            break;
        }

        switch (type)
        {
        case NUMBER:                strncpy(type_str,"NUMBER",20);              break;
        case VARIABLE:              strncpy(type_str,"VARIABLE",20);            break;
        case EXPONENT:              strncpy(type_str,"EXPONENT",20);            break;
        case PLACEHOLDER_NUMBER:    strncpy(type_str,"PLACEHOLDER_NUMBER",20);  break;
        case MULTIPLICATION:        strncpy(type_str,"MULTIPLICATION",20);      break;
        case DIVISION:              strncpy(type_str,"DIVISION",20);            break;
        case ADDITION:              strncpy(type_str,"ADDITION",20);            break;
        case SUBTRACTION:           strncpy(type_str,"SUBTRACTION",20);         break;
        case POWER:                 strncpy(type_str,"POWER",20);               break;
        case PARENTHESE_OPEN:       strncpy(type_str,"PARENTHESE_OPEN",20);     break;
        case PARENTHESE_CLOSE:      strncpy(type_str,"PARENTHESE_CLOSE",20);    break;
        default: break;
        }

        printf("content: %c\ttype: %s\n",
            tokens[i].token_c, type_str);
    }
}

















