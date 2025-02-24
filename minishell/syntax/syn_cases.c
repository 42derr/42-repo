/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_cases.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:44:11 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:44:12 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_open_parenthesis(t_mini *mini)
{
	if (mini->syn.current.type == LEFT_PARENTHESIS
		&& mini->syn.i != 0
		&& !(mini->syn.prev.type == LEFT_PARENTHESIS
			|| mini->syn.prev.type == BACKGROUND
			|| token_is_operator(mini->syn.prev, mini)))
	{
		syntax_msg(mini, "syntax error near unexpected token `('\n");
		return (2);
	}
	open_parenthesis(mini);
	update_next_token(mini);
	if (syntax_check(mini) != 0)
	{
		syntax_msg(mini, "syntax error: unexpected end of file\n");
		return (2);
	}
	return (0);
}

int	syntax_close_parenthesis(t_mini *mini)
{
	if (mini->syn.parenthesis + 1 == 0
		|| (mini->syn.prev.type == LEFT_PARENTHESIS
			|| token_is_operator(mini->syn.prev, mini)
			|| token_is_redirect(mini->syn.prev, mini)))
	{
		if (mini->syn.prev.type == LEFT_PARENTHESIS
			&& mini->syn.parenthesis > 1)
		{
			close_parenthesis(mini);
			update_next_token(mini);
			return (1);
		}
		syntax_msg(mini, "syntax error near unexpected token `)'\n");
		return (2);
	}
	close_parenthesis(mini);
	update_next_token(mini);
	if (syntax_cmd_after_paren(mini))
		return (2);
	return (0);
}

int	syntax_operators_redirects_end(t_mini *mini)
{
	if (token_is_operator(mini->syn.current, mini)
		|| mini->syn.current.type == BACKGROUND)
	{
		if (mini->syn.i >= 0 && (token_is_operator(mini->syn.prev, mini)
				|| token_is_redirect(mini->syn.prev, mini)
				|| mini->syn.prev.type == BACKGROUND
				|| mini->syn.prev.type == LEFT_PARENTHESIS))
			return (unexpected_token_msg(mini), 2);
	}
	else if (token_is_redirect(mini->syn.current, mini))
	{
		if (mini->syn.current.type == HERE_DOC)
			mini->syn.heredoc++;
		if (mini->syn.i != 0 && token_is_redirect(mini->syn.prev, mini))
			return (unexpected_token_msg(mini), 2);
	}
	else if (mini->all_token[mini->syn.i + 1].value == NULL)
	{
		if (syntax_pair_check(mini, mini->all_token[mini->syn.i].value))
			return (2);
	}
	return (0);
}

int	syntax_pair_check(t_mini *mini, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && !mini->syn.dq && !mini->syn.bt)
			mini->syn.sq = !mini->syn.sq;
		else if (arg[i] == '\"' && !mini->syn.sq && !mini->syn.bt)
			mini->syn.dq = !mini->syn.dq;
		else if (arg[i] == '`' && !mini->syn.sq)
		{
			mini->syn.bt = !mini->syn.bt;
			mini->syn.backtick = 1;
		}
		i++;
	}
	if (mini->syn.sq)
		ft_putstr_fd("unexpected EOF while looking for matching `\'\'\n", 2);
	else if (mini->syn.bt)
		ft_putstr_fd("unexpected EOF while looking for matching ``\'\n", 2);
	else if (mini->syn.dq)
		ft_putstr_fd("unexpected EOF while looking for matching `\"\'\n", 2);
	if (mini->syn.sq || mini->syn.dq || mini->syn.bt)
		ft_putstr_fd("syntax error: unexpected end of file\n", 2);
	return (mini->syn.sq || mini->syn.dq || mini->syn.bt);
}

int	syntax_arithmetic_check(t_mini *mini)
{
	t_parenthesis	*prev;
	t_parenthesis	*current;

	prev = NULL;
	current = mini->syn.parenthesis_info;
	if (current == NULL || current->next == NULL)
		return (0);
	while (current)
	{
		if (prev != NULL
			&& current->open - prev->open == 1
			&& prev->close - current->close == 1)
		{
			ft_putstr_fd("does not support arithmetic evaluation\n", 2);
			mini->syn.msg = 1;
			return (mini->exit_status = 127, 127);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
