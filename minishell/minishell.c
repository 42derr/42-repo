#include "minishell.h"

void handle_sigint(int sig) 
{
    printf("Minishell@AD: \n");
    rl_on_new_line();
    rl_redisplay();
}

int new_anjing(void)
{
        char *input = readline("Minishell@AD: ");
        if (input == NULL)
            return (printf("bye bye :(\n"),1);
        printf("Test: %s\n", input);
        add_history(input);
        free(input);
        return (1);
}

int main(void) {
    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    while (1)
        if (new_anjing() == 1)
            break ;
    rl_clear_history();
    return 0;
}
