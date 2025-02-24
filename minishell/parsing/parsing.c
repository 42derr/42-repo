/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:43:54 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:43:55 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing(t_mini *mini)
{
	t_node	*final;
	int		max;

	max = 0;
	while (mini->all_token[max].value != NULL)
		max++;
	final = parse_input(mini->all_token, 0, max, mini);
	mini->all_node = final;
}

t_node	*parse_input(t_token *token_buffer, int start, int end, t_mini *mini)
{
	int		current;
	t_node	*node;

	if (start >= end)
		return (NULL);
	current = get_next_root(token_buffer, start, end);
	if (current == -2)
		return (NULL);
	if (current == -1)
		return (new_command_node(token_buffer, start, end, mini));
	node = create_node(mini);
	if (token_buffer[current].type == RIGHT_PARENTHESIS
		|| token_buffer[current].type == LEFT_PARENTHESIS)
	{
		free(node);
		return (new_parenthesis_node(token_buffer, start, end, mini));
	}
	else
	{
		node->token = &(token_buffer[current]);
		node->left = parse_input(token_buffer, start, current, mini);
		node->right = parse_input(token_buffer, current + 1, end, mini);
		return (node);
	}
}
