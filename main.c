#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_TOKENS                 1000
#define ERROR_PRINT(args ...)       fprintf(stderr, args)

static int x = 0;

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
    char token_c;
    TYPE type;
} token_t;


void generate_token(token_t* token, const TYPE type, const char content)
{
    *token = (token_t) {
        .token_c = content,
        .type = type,
    };
}

void print_tokens(const token_t* tokens)
{
    for (int i = 0; i < SIZE_TOKENS; i++)
    {
        if (tokens[i].type == UNINITIALIZED) break;

        printf("content: %c     type: %d\n",
            tokens[i].token_c, tokens[i].type);
    }
}

bool check_left_token_mul_or_div(const token_t* tokens, const int index)
{
    TYPE type_left = UNINITIALIZED;
    if (index - 1 >= 0)
    {
        type_left = tokens[index - 1].type;
    }

    if (type_left == MULTIPLICATION || type_left == DIVISION) return true;
    return false;
}

bool check_right_token_mul_or_div(const token_t* tokens, const int index)
{
    TYPE type_right = UNINITIALIZED;
    if (index + 1 < SIZE_TOKENS)
    {
        type_right = tokens[index + 1].type;
    }

    if (type_right == MULTIPLICATION || type_right == DIVISION) return true;
    return false;
}

void translate_into_formula(const token_t* tokens)
{
    token_t* token_buffer = malloc(sizeof(token_t) * 10);
    int token_buffer_index = 0;
    bool parentheses = false;
    for (int i = 0; i < SIZE_TOKENS; i++)
    {
        const char token_c = tokens[i].token_c;
        const TYPE type = tokens[i].type;

        if (type == PARENTHESE_CLOSE)
        {
            parentheses = false;
            break;
        }

        if (parentheses)
        {
            token_buffer[token_buffer_index] = tokens[i];
            token_buffer_index++;
        }

        if (type == UNINITIALIZED) break;
        if (type == PARENTHESE_OPEN)
        {
            parentheses = true;
            continue;
        }

        if (type == ADDITION || type == SUBTRACTION)
        {
            if (check_left_token_mul_or_div(tokens, i))
            {

            }
            if (check_right_token_mul_or_div(tokens, i))
            {

            }
        }
        if (type == MULTIPLICATION)
        {

        }
        if (type == DIVISION)
        {

        }
    }
}


int main(void)
{
    const char* integral = "X ^ 3 + 2 x ^ 2 - 4 x + 5";

    token_t* tokens = malloc(sizeof(token_t) * SIZE_TOKENS);
    if (tokens == nullptr)
    {
        ERROR_PRINT("Memory allocation failed!");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < SIZE_TOKENS; i++)
    {
        tokens[i] = (token_t){
            .token_c = '0',
            .type = UNINITIALIZED
        };
    }

    int token_index = 0;
    TYPE type = UNINITIALIZED;

    for (int i = 0; i < strlen(integral); i++)
    {
        char c = integral[i];
        if (isspace(c) || iscntrl(c)) continue;

        if (isdigit(c)) type = NUMBER;

        if (isalpha(c))
        {
            type = VARIABLE;
            if (isupper(c))
            {
                c = (char)tolower(c);
            }
        }

        switch (c)
        {
        case MULTIPLICATION: type = MULTIPLICATION; break;
        case DIVISION: type = DIVISION; break;
        case ADDITION: type = ADDITION; break;
        case SUBTRACTION: type = SUBTRACTION; break;
        case POWER: type = POWER; break;
        case PARENTHESE_OPEN: type = PARENTHESE_OPEN; break;
        case PARENTHESE_CLOSE: type = PARENTHESE_CLOSE; break;
        default: break;
        }

        generate_token(&tokens[token_index], type, c);
        token_index++;
    }

    print_tokens(tokens);
    translate_into_formula(tokens);

    free(tokens);
    return EXIT_SUCCESS;
}


