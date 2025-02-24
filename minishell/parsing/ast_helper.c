/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:43:31 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:43:32 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*create_node(t_mini *mini)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		clean_exit("malloc", mini);
	node->token = NULL;
	node->left = NULL;
	node->right = NULL;
	node->action = NULL;
	return (node);
}

void	skip_through_parenthesis(t_token *token_buffer, int start,
									int end, int *i)
{
	while ((*i) < end && token_buffer[(*i)].value != NULL)
	{
		if (token_buffer[(*i)].type == LEFT_PARENTHESIS)
		{
			(*i)++;
			skip_through_parenthesis(token_buffer, start, end, i);
		}
		else if (token_buffer[(*i)].type == RIGHT_PARENTHESIS)
		{
			(*i)++;
			return ;
		}
		else
			(*i)++;
	}
}

int	get_next_root(t_token *token_buffer, int start, int end)
{
	int	i;
	int	precedence;

	i = start;
	precedence = -1;
	while (i < end && token_buffer[i].value != NULL)
	{
		if (precedence == -1 && is_this_operator(token_buffer[i].type))
			precedence = i;
		if (token_buffer[i].type == LEFT_PARENTHESIS
			|| token_buffer[i].type == RIGHT_PARENTHESIS)
		{
			i++;
			skip_through_parenthesis(token_buffer, start, end, &i);
			i--;
		}
		if (precedence != -1 && is_this_operator(token_buffer[i].type)
			&& ((token_buffer[i].type <= token_buffer[precedence].type)
				|| token_buffer[i].type < 2))
			precedence = i;
		i++;
	}
	return (precedence);
}

int	get_next_action(t_token *token_buffer, int start, int end)
{
	int	save;

	save = -1;
	while (start < end)
	{
		if (token_buffer[start].type == LEFT_PARENTHESIS)
		{
			start++;
			skip_through_parenthesis(token_buffer, start, end, &start);
			if (start >= end)
				break ;
		}
		if (token_buffer[start].type == REDIRECT_INPUT
			|| token_buffer[start].type == REDIRECT_OUTPUT
			|| token_buffer[start].type == HERE_DOC
			|| token_buffer[start].type == APPEND
			|| token_buffer[start].type == REDIRECT_IO)
			save = start;
		start++;
	}
	return (save);
}

int	is_this_operator(int num)
{
	return (num == PIPE
		|| num == AND
		|| num == OR
		|| num == LEFT_PARENTHESIS
		|| num == RIGHT_PARENTHESIS);
}
