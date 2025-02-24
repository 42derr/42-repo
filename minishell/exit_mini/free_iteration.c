/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_iteration.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:49:16 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/18 21:10:05 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all_node(t_node *node)
{
	if (!node)
		return ;
	if (!node->token)
		return ;
	if (node->token->type == CMDS)
	{
		free(node->token->value);
		free(node->token);
	}
	else if (node->token->type == PARENTHESIS)
	{
		free(node->token->value);
		free(node->token);
	}
	free_all_node(node->left);
	free_all_node(node->right);
	free_all_node(node->action);
	free(node);
}

void	free_syntax(t_mini *mini)
{
	t_parenthesis	*current;
	t_parenthesis	*next;

	current = mini->syn.parenthesis_info;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_wild_card(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->all_token)
	{
		while (mini->all_token[i].value)
		{
			if (mini->all_token[i].type == WILDCARD)
				ft_free_2d(&(mini->all_token[i].wild));
			i++;
		}
		free(mini->all_token);
		mini->all_token = NULL;
	}
}

void	free_syntax_hd(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->syn.parenthesis_info)
	{
		free_syntax(mini);
		mini->syn.parenthesis_info = NULL;
	}
	if (mini->hd)
	{
		while (i < mini->syn.heredoc)
		{
			if (mini->hd[i] != 0)
				close(mini->hd[i]);
			i++;
		}
		free(mini->hd);
		mini->hd = NULL;
	}
	mini->syn = (t_syntax){0};
}

void	free_iteration(t_mini *mini)
{
	if (mini->input)
	{
		free(mini->input);
		mini->input = NULL;
	}
	if (mini->all_node)
	{
		free_all_node(mini->all_node);
		mini->all_node = NULL;
	}
	free_wild_card(mini);
	if (mini->all_input)
	{
		ft_free_2d(&mini->all_input);
		mini->all_input = NULL;
	}
	if (mini->cmds)
	{
		ft_free_2d(&mini->cmds);
		mini->cmds = NULL;
	}
	free_syntax_hd(mini);
}
