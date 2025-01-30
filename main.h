//
// Created by sven on 30.01.25.
//

#ifndef MAIN_H
#define MAIN_H

#define SIZE_TOKENS                 1000
#define ERROR_PRINT(args ...)       fprintf(stderr, args)

typedef enum type
{
    NUMBER,
    VARIABLE,
    EXPONENT,
    UNINITIALIZED,

    PARENTHESE_OPEN     = 40,
    PARENTHESE_CLOSE    = 41,
    MULTIPLICATION      = 42,
    ADDITION            = 43,
    SUBTRACTION         = 45,
    DIVISION            = 47,
    POWER               = 94,
} type_t;

/*
typedef enum operation
{
    ADD,
    SUBTRACT,
    DIVIDE,
    MULTIPLY,
    OTHER,
    UNINITIALIZED_OPERATION,
}operation_t;
*/

typedef struct token
{
    char token_c;
    type_t type;
} token_t;

typedef struct section
{
    char* token_arr;
    int size;

    type_t type;
}section_t;


void generate_token(token_t* token, type_t type, char content);
void print_tokens(const token_t* tokens);
bool check_left_token_mul_or_div(const token_t* tokens, int index);
bool check_next_token_mul_or_div(const token_t* tokens, int index);
bool check_left_token_number(const token_t* tokens, int index);
bool check_next_token_number(const token_t* tokens, int index);

void construct_number_with_multiple_digits(section_t* section, type_t type, char number_c);
void translate_into_formula(const token_t* tokens);

#endif //MAIN_H
