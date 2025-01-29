#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_PRINT(args ...)    fprintf(stderr, args)

typedef enum TYPE
{
    NUMBER,
    VARIABLE,
    EXPONENT,
    UNINITIALIZED,

    PARENTHESE_OPEN = 40,
    PARENTHESE_CLOSE = 41,
    MULTIPLICATION = 42,
    ADDITION = 43,
    SUBTRACTION = 45,
    DIVISION = 47,
    POWER = 94,
} TYPE;

typedef struct token
{
    char content;
    TYPE type;
} token_t;


void generate_token(token_t* token, const TYPE type, const char content)
{
    *token = (token_t) {
        .content = content,
        .type = type,
    };
}

void print_tokens(const token_t* tokens)
{
    for (int i = 0; i < 1000; i++)
    {
        if (tokens[i].type == UNINITIALIZED)
        {
            break;
        }

        printf("content: %c     type: %d\n", tokens[i].content, tokens[i].type);
    }

}

int main(void)
{
    const char* integral = "x ^ 3 + 2 x ^ 2 - 4 x + 5";

    token_t* tokens = malloc(sizeof(token_t) * 1000);
    if (tokens == nullptr)
    {
        ERROR_PRINT("Memory allocation failed!");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 1000; i++)
    {
        tokens[i] = (token_t){
            .content = '0',
            .type = UNINITIALIZED
        };
    }

    int token_index = 0;
    TYPE type = UNINITIALIZED;

    for (int i = 0; i < strlen(integral); i++)
    {
        const char c = integral[i];
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
        }

        switch (c)
        {
        case MULTIPLICATION:
            type = MULTIPLICATION;
            break;

        case DIVISION:
            type = DIVISION;
            break;

        case ADDITION:
            type = ADDITION;
            break;

        case SUBTRACTION:
            type = SUBTRACTION;
            break;

        case POWER:
            type = POWER;
            break;

        case PARENTHESE_OPEN:
            type = PARENTHESE_OPEN;
            break;

        case PARENTHESE_CLOSE:
            type = PARENTHESE_CLOSE;
            break;

        default:
            break;
        }

        generate_token(&tokens[token_index], type, c);
        token_index++;
    }

    print_tokens(tokens);

    free(tokens);
    return EXIT_SUCCESS;
}


