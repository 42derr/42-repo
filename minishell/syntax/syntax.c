/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:44:21 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:44:22 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_check(t_mini *mini)
{
	int	save;

	mini->syn.current = mini->all_token[mini->syn.i];
	while (mini->syn.current.value != NULL)
	{
		if (token_is_open_parenthesis(mini->syn.current, mini))
		{
			if (syntax_open_parenthesis(mini) != 0)
				return (mini->exit_status = 2, 2);
			continue ;
		}
		else if (mini->syn.current.type == RIGHT_PARENTHESIS)
		{
			save = syntax_close_parenthesis(mini);
			if (save == 1)
				continue ;
			else
				return (mini->exit_status = save, save);
		}
		else if (syntax_operators_redirects_end(mini) != 0)
			return (mini->exit_status = 2, 2);
		update_next_token(mini);
	}
	return (syntax_end(mini));
}

int	syntax_end(t_mini *mini)
{
	if (token_is_operator(mini->syn.prev, mini))
		return (syntax_msg(mini, "syntax error: unexpected end of file\n"), 2);
	if (token_is_redirect(mini->syn.prev, mini))
	{
		syntax_msg(mini, "syntax error near unexpected token `newline'\n");
		return (2);
	}
	if (mini->syn.parenthesis == 0 && unsupported_msg(mini))
		return (mini->exit_status = 127, 127);
	if (mini->syn.parenthesis == 0)
		return (syntax_arithmetic_check(mini));
	return (mini->exit_status = 2, 2);
}
