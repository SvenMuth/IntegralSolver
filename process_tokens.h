//
// Created by sven on 30.01.25.
//

#ifndef PROCESS_TOKENS_H
#define PROCESS_TOKENS_H

#include "tokenizer.h"


void clear_char_buffer(char* buffer);
void construct_number_buffer(char* buffer, char number, int digit);

void strip_numbers_token(token_t* tokens, token_t* token_with_placeholders, int* numbers);
void execute_tokens(token_t* tokens, const int* numbers, double* result, double* x);

bool check_is_token_mul_or_div(token_t* tokens, int index);
bool check_is_token_number(token_t* tokens, int index);
bool check_is_token_power(token_t* tokens, int index);




#endif //PROCESS_TOKENS_H
