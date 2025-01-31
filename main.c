
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "commons.h"
#include "process_tokens.h"
#include "tokenizer.h"


int main(void)
{
    //constexpr char integral[] = "x ^ 30 + 2 x ^ 2 - 4 x + 5";
    constexpr char integral[] = "2 - 4 + 5";
    token_t* tokens = tokenize(integral);

    int* numbers_from_integral = malloc(sizeof(int) * SIZE_TOKENS);

    token_t* token_with_placeholders = default_initialization_tokens();
    strip_numbers_token(tokens, token_with_placeholders, numbers_from_integral);

    double result = 0;
    execute_tokens(token_with_placeholders, numbers_from_integral, &result);
    printf("%f", result);

    free(numbers_from_integral);
    free(tokens);
    return EXIT_SUCCESS;
}























