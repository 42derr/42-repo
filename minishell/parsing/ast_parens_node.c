/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parens_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:43:37 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:43:38 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_parenthesis_token(t_mini *mini)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		clean_exit("malloc", mini);
	token->value = ft_strdup("PARENTHESIS");
	if (!token->value)
	{
		free(token);
		clean_exit("malloc", mini);
	}
	token->type = PARENTHESIS;
	return (token);
}

t_node	*new_parenthesis_node(t_token *token_buffer, int start,
								int end, t_mini *mini)
{
	t_node	*node;
	t_token	*token;
	int		i;

	i = 0;
	token = create_parenthesis_token(mini);
	node = create_node(mini);
	node->token = token;
	node->action = new_action_node(token_buffer, start, end, mini);
	while (start < end)
	{
		if (token_buffer[start].type == LEFT_PARENTHESIS)
		{
			start++;
			i = start;
			skip_through_parenthesis(token_buffer, start, end, &i);
			break ;
		}
		start++;
	}
	node->left = parse_input(token_buffer, start, i - 1, mini);
	return (node);
}
