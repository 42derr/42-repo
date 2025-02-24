/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:43:25 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:43:28 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*new_command_node(t_token *token_buffer, int start,
							int end, t_mini *mini)
{
	t_node	*node;
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		clean_exit("malloc", mini);
	token->value = ft_strdup("CMDS");
	if (!token->value)
	{
		free(token);
		clean_exit("ft_strdup", mini);
	}
	token->type = CMDS;
	node = create_node(mini);
	node->token = token;
	node->action = new_action_node(token_buffer, start, end, mini);
	node->left = new_args_node(token_buffer, start, end, mini);
	return (node);
}

t_node	*new_action_node(t_token *token_buffer, int start,
							int end, t_mini *mini)
{
	int		current;
	t_node	*node;

	if (start >= end)
		return (NULL);
	current = get_next_action(token_buffer, start, end);
	if (current == -1)
		return (NULL);
	node = create_node(mini);
	node->left = new_action_node(token_buffer, start, current, mini);
	node->token = &(token_buffer[current]);
	node->right = create_node(mini);
	node->right->token = &(token_buffer[current + 1]);
	return (node);
}

t_node	*new_args_node(t_token *token_buffer, int start, int end, t_mini *mini)
{
	t_node	*node;

	if (start >= end)
		return (NULL);
	if (token_buffer[start].type == REDIRECT_INPUT
		|| token_buffer[start].type == REDIRECT_OUTPUT
		|| token_buffer[start].type == APPEND
		|| token_buffer[start].type == HERE_DOC
		|| token_buffer[start].type == REDIRECT_IO)
	{
		if (start + 2 >= end)
			return (NULL);
		return (new_args_node(token_buffer, start + 2, end, mini));
	}
	node = create_node(mini);
	node->token = &(token_buffer[start]);
	node->left = new_args_node(token_buffer, start + 1, end, mini);
	return (node);
}
