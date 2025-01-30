//
// Created by sven on 30.01.25.
//

#ifndef MAIN_H
#define MAIN_H

#define SIZE_TOKENS                 1000
#define ERROR_PRINT(args ...)       fprintf(stderr, args)

typedef enum TYPE
{
    NUMBER,
    VARIABLE,
    EXPONENT,
    UNINITIALIZED_TYPE,

    PARENTHESE_OPEN     = 40,
    PARENTHESE_CLOSE    = 41,
    MULTIPLICATION      = 42,
    ADDITION            = 43,
    SUBTRACTION         = 45,
    DIVISION            = 47,
    POWER               = 94,
} TYPE;

typedef enum OPERATION
{
    ADD,
    SUBTRACT,
    DIVIDE,
    MULTIPLY,
    OTHER,
    UNINITIALIZED_OPERATION,
}OPERATION;

typedef struct token
{
    char token_c;
    TYPE type;
} token_t;

typedef struct section
{
    token_t* token;
    int size;

    OPERATION operation;
    TYPE type;
}section_t;


void generate_token(token_t* token, TYPE type, char content);
void print_tokens(const token_t* tokens);
bool check_left_token_mul_or_div(const token_t* tokens, int index);
bool check_right_token_mul_or_div(const token_t* tokens, int index);
bool check_left_token_number(const token_t* tokens, int index);
bool check_right_token_number(const token_t* tokens, int index);

int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
int power(int a);

void construct_number_with_multiple_digits(section_t* section, TYPE type, char number_c);
void translate_into_formula(const token_t* tokens);

#endif //MAIN_H
