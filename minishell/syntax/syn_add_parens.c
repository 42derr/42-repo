/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_add_parens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:44:07 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:44:08 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_parenthesis(t_mini *mini)
{
	t_parenthesis	*new;
	t_parenthesis	*current;

	mini->syn.parenthesis++;
	new = malloc(sizeof(t_parenthesis));
	if (!new)
		clean_exit("malloc", mini);
	new->open = mini->syn.i;
	new->close = 0;
	new->next = NULL;
	if (mini->syn.parenthesis_info == NULL)
	{
		mini->syn.parenthesis_info = new;
		return ;
	}
	current = mini->syn.parenthesis_info;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	close_parenthesis(t_mini *mini)
{
	t_parenthesis	*prev;
	t_parenthesis	*current;

	mini->syn.parenthesis--;
	prev = NULL;
	current = mini->syn.parenthesis_info;
	if (current->next == NULL)
	{
		current->close = mini->syn.i;
		return ;
	}
	while (current)
	{
		if (prev != NULL && current->close != 0 && prev->close == 0)
		{
			prev->close = mini->syn.i;
			return ;
		}
		prev = current;
		current = current->next;
	}
	prev->close = mini->syn.i;
}
