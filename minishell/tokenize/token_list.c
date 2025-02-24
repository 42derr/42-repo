/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:43:07 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:43:08 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*add_token(char **input)
{
	t_token	*token_buffer;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (input[len])
		len++;
	token_buffer = malloc(sizeof(t_token) * (len + 1));
	if (!token_buffer)
		return (NULL);
	while (input[i])
	{
		if (get_token(input[i], &token_buffer[i]))
		{
			while (i-- > 0)
			{
				if (token_buffer[i].type == WILDCARD)
					ft_free_2d(&token_buffer[i].wild);
			}
			return (free(token_buffer), NULL);
		}
		i++;
	}
	return (token_buffer[i].value = NULL, token_buffer);
}

int	get_token(char *cmds, t_token *new_token)
{
	new_token->type = get_token_type(cmds);
	new_token->value = cmds;
	new_token->wild = NULL;
	if (new_token->type == WILDCARD)
	{
		new_token->wild = get_wildcard(new_token->value, 0);
		if (!new_token->wild)
			return (1);
	}
	return (0);
}

t_num	get_token_type(char *value)
{
	if (ft_strncmp(value, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(value, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(value, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(value, "&", 1) == 0)
		return (BACKGROUND);
	else if (ft_strncmp(value, "(", 1) == 0)
		return (LEFT_PARENTHESIS);
	else if (ft_strncmp(value, ")", 1) == 0)
		return (RIGHT_PARENTHESIS);
	else if (ft_strncmp(value, "\'", 1) == 0)
		return (SINGLE_QUOTE);
	else if (ft_strncmp(value, "\"", 1) == 0)
		return (DOUBLE_QUOTE);
	else if (ft_strncmp(value, "`", 1) == 0)
		return (BACKTICK);
	else if (ft_strncmp(value, "$?", 2) == 0)
		return (EXIT_STATUS);
	else if (ft_strncmp(value, "$", 1) == 0)
		return (ENV_VAR);
	else
		return (get_token_type_cont(value));
}

t_num	get_token_type_cont(char *value)
{
	if (ft_strncmp(value, "<<<", 3) == 0)
		return (HERE_STRING);
	else if (ft_strncmp(value, "<<", 2) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(value, ">>", 2) == 0)
		return (APPEND);
	else if (ft_strncmp(value, "<>", 2) == 0)
		return (REDIRECT_IO);
	else if (ft_strncmp(value, ">|", 2) == 0)
		return (FORCED_OUTPUT);
	else if (ft_strncmp(value, ">&", 2) == 0 || ft_strncmp(value, "<&", 2) == 0)
		return (FD_DUP);
	else if (ft_strncmp(value, "<(", 2) == 0)
		return (INPUT_SUBSTITUTE);
	else if (ft_strncmp(value, ">(", 2) == 0)
		return (OUTPUT_SUBSTITUTE);
	else if (ft_strncmp(value, "<", 1) == 0)
		return (REDIRECT_INPUT);
	else if (ft_strncmp(value, ">", 1) == 0)
		return (REDIRECT_OUTPUT);
	else if (ft_strchr(value, '*') || ft_strchr(value, '?'))
		return (WILDCARD);
	else
		return (ARGS);
}
