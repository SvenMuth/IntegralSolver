//
// Created by sven on 30.01.25.
//

#ifndef PROCESS_TOKENS_H
#define PROCESS_TOKENS_H

#include "tokenizer.h"

typedef struct char_buffer
{
    char buffer[4];
    size_t length;
}char_buffer_t;

void strip_numbers_token(token_t* tokens);
void execute_tokens(const token_t* tokens);

bool check_is_token_mul_or_div(const token_t* tokens, int index);
bool check_is_token_number(const token_t* tokens, int index);




#endif //PROCESS_TOKENS_H
