//
// Created by sven on 30.01.25.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum type
{
    NUMBER,
    VARIABLE,
    EXPONENT,
    UNINITIALIZED,

    PLACEHOLDER_NUMBER  = 37,
    PARENTHESE_OPEN     = 40,
    PARENTHESE_CLOSE    = 41,
    MULTIPLICATION      = 42,
    ADDITION            = 43,
    SUBTRACTION         = 45,
    DIVISION            = 47,
    POWER               = 94,
} type_t;

typedef struct token
{
    char token_c;
    type_t type;
} token_t;

token_t* default_initialization_tokens(void);
token_t* tokenize(const char* integral);
void generate_token(token_t* token, type_t type, char content);
void print_tokens(const token_t* tokens);

#endif //TOKENIZER_H




























