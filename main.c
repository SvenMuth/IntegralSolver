
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "process_tokens.h"
#include "tokenizer.h"


int main(void)
{
    constexpr char integral[] = "x ^ 30 + 2 x ^ 2 - 4 x + 5";

    token_t* tokens = tokenize(integral);
    strip_numbers_token(tokens);

    free(tokens);
    return EXIT_SUCCESS;
}























