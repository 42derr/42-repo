/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputri-a <aputri-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:46:10 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 00:49:34 by aputri-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_filename_expand(char **expansion, t_node *node,
							t_mini *mini, int *expand)
{
	(*expansion) = node->right->token->value;
	if (node->token->type != HERE_DOC && ft_strchr(*expansion, '$'))
	{
		*expansion = expand_env(*expansion, mini, 0, 0);
		*expand = 1;
		if ((*expansion)[0] == '\0' || ft_strchr(*expansion, ' '))
		{
			ft_print_errs(node->right->token->value, ": ambiguous redirect",
				NULL, NULL);
			free(*expansion);
			return (1);
		}
	}
	return (0);
}

int	handle_wildcard_redirect(char **filename, t_node *node)
{
	int	file_counts;

	file_counts = ft_arrlen(node->right->token->wild);
	if (file_counts > 1)
	{
		ft_print_errs(node->right->token->value, ": ambiguous redirect",
			NULL, NULL);
		return (1);
	}
	if (file_counts == 0)
	{
		(*filename) = node->right->token->value;
		return (0);
	}
	(*filename) = node->right->token->wild[0];
	return (0);
}

int	run_action(t_mini *mini, t_node *node, int expand)
{
	char	*filename;

	if (node == NULL)
		return (0);
	if (node->left)
	{
		if (run_action(mini, node->left, 0) == 1)
			return (1);
	}
	if (node->token->type != HERE_DOC && node->right->token->type == WILDCARD)
	{
		if (handle_wildcard_redirect(&filename, node))
			return (1);
	}
	else if (handle_filename_expand(&filename, node, mini, &expand))
		return (1);
	if (node->token->type == REDIRECT_INPUT)
		return (run_redirect_input(&filename, expand, mini));
	else if (node->token->type == REDIRECT_OUTPUT)
		return (run_redirect_output(&filename, expand, mini));
	else if (node->token->type == APPEND)
		return (run_append(&filename, expand, mini));
	else if (node->token->type == REDIRECT_IO)
		return (run_redirect_io(&filename, expand, mini));
	return (run_heredoc(node->right->token->hd, filename, mini));
}
