
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "process_tokens.h"
#include "tokenizer.h"

static double x = 0;


int main(void)
{
    constexpr char integral[] = "x ^ 3 + 2 x ^ 2 - 4 x + 5";

    token_t* tokens = tokenize(integral);
    translate_into_formula(tokens);

    free(tokens);
    return EXIT_SUCCESS;
}























