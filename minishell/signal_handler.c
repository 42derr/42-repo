#include "minishell.h"

void handle_sigint(int sig) 
{
    if (!sig)
        return ; //check this
    printf("Minishell@AD: \n");
    rl_on_new_line();
    rl_redisplay();
}

int new_line(void)
{
    char *input = readline("Minishell@AD: ");
    t_token *token_buffer;

    if (input == NULL)
        return (printf("bye bye :(\n"),1);
    printf("Test: %s\n", input);
    add_history(input);
    token_buffer = tokenization(input);
    parsing(token_buffer);
    free(input);
    return (0);
}