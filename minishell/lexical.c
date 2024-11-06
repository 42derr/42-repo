#include "minishell.h"

e_num   get_token_type(char *value)
{
    if (ft_strncmp(value, "\'", 1) == 0)
        return (SINGLE_QUOTE);//take note
    else if (ft_strncmp(value, "\"", 1) == 0)
        return (DOUBLE_QUOTE);// take note
    else if (ft_strncmp(value, "<<", 2) == 0)
        return (HERE_DOC);
    else if (ft_strncmp(value, ">>", 2) == 0)
        return (APPEND);
    else if (ft_strncmp(value, "<", 1) == 0)
        return (REDIRECT_INPUT);
    else if (ft_strncmp(value, ">", 1) == 0)
        return (REDIRECT_OUTPUT);
    else if (ft_strncmp(value, "||", 2) == 0)
        return (OR);
    else if (ft_strncmp(value, "|", 1) == 0)
        return (PIPE);
    else if (ft_strncmp(value, "$?", 2) == 0)
        return (EXIT_STATUS);
    else if (ft_strncmp(value, "$", 1) == 0)
        return (ENV_VAR);
    else if (ft_strncmp(value, "&&", 2) == 0)
        return (AND);
    else if (ft_strncmp(value, "(", 1) == 0)
        return (PARENTHESIS);//take note (hahhahahaha || yey)
    else if (ft_strncmp(value, "*", 1) == 0)
        return (WILDCARD);
    else 
        return (ARGS);
}

t_token *get_token(char *cmds)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
    new_token->value = cmds;
    new_token->type = get_token_type(cmds);

    return (new_token);
}

t_token	*add_token(char **input)
{
	t_token	*token_buffer;
    int i;

    i = 0;

	token_buffer = malloc(sizeof(t_token) * 1000); // need to change this later
    while (input[i])
    {
        token_buffer[i] = *get_token(input[i]);
        i++;
    }
    token_buffer[i].value = NULL;
    return (token_buffer);
}

t_token    *tokenization(char *arg)
{
    int     i;
    char    **input;
	t_token	*token_buffer;

    i = 0;
    input = cmds_handler(arg);
    token_buffer =  add_token(input);
    return (token_buffer);
}
