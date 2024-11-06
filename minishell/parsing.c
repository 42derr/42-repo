#include "minishell.h"

void   angel_helper(int num)
{
    if (num == 0)
        printf ("%s", "SINGLE_QUOTE\n");
    else if (num == 1)
        printf ("%s", "DOUBLE_QUOTE\n");
    else if (num == 2)
        printf ("%s", "REDIRECT_INPUT\n");
    else if (num == 3)
        printf ("%s", "REDIRECT_OUTPUT\n");
    else if (num == 4)
        printf ("%s", "HERE_DOC\n");
    else if (num == 5)
        printf ("%s", "APPEND\n");
    else if (num == 6)
        printf ("%s", "PIPE\n");
    else if (num == 7)
        printf ("%s", "EXIT_STATUS\n");
    else if (num == 8)
        printf ("%s", "ENV_VAR\n");
    else if (num == 9)
        printf ("%s", "AND\n");
    else if (num == 10)
        printf ("%s", "OR\n");
    else if (num == 11)
        printf ("%s", "PARENTHESIS\n");
    else if (num == 12)
        printf ("%s", "WILDCARD\n");
    else 
        printf ("%s", "ARGS\n");
}

void    parsing(t_token *token_buffer)
{
    int i = 0;

    while (token_buffer[i].value != NULL)
    {
        printf("%s\n", token_buffer[i].value);
        angel_helper(token_buffer[i].type);
        printf("\n");
        i++;
    }
}