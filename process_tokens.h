//
// Created by sven on 30.01.25.
//

#ifndef PROCESS_TOKENS_H
#define PROCESS_TOKENS_H

#include "tokenizer.h"
#include "commons.h"

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

typedef struct section
{
    char* token_arr;
    int size;

    type_t type;
}section_t;


bool check_left_token_mul_or_div(const token_t* tokens, int index);
bool check_next_token_mul_or_div(const token_t* tokens, int index);
bool check_left_token_number(const token_t* tokens, int index);
bool check_next_token_number(const token_t* tokens, int index);

void construct_number_with_multiple_digits(section_t* section, type_t type, char number_c);
void translate_into_formula(const token_t* tokens);


#endif //PROCESS_TOKENS_H
