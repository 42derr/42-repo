/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputri-a <aputri-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:44:16 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 00:04:36 by aputri-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_next_token(t_mini *mini)
{
	unsupported_check(mini->all_token[mini->syn.i], mini);
	mini->syn.prev = mini->all_token[mini->syn.i];
	mini->syn.i++;
	mini->syn.current = mini->all_token[mini->syn.i];
}

int	syntax_cmd_after_paren(t_mini *mini)
{
	if (mini->syn.current.value && token_is_cmd(mini->syn.current, mini))
	{
		if (mini->syn.msg != 0)
			return (2);
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(mini->all_token[mini->syn.i].value, 2);
		ft_putstr_fd("'\n", 2);
		mini->syn.msg = 1;
		return (2);
	}
	return (0);
}

void	syntax_msg(t_mini *mini, char *msg)
{
	if (mini->syn.msg != 0)
		return ;
	ft_putstr_fd(msg, 2);
	mini->syn.msg = 1;
}

void	unexpected_token_msg(t_mini *mini)
{
	if (mini->syn.msg != 0)
		return ;
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(mini->syn.current.value, 2);
	ft_putstr_fd("'\n", 2);
	mini->syn.msg = 1;
}

int	unsupported_msg(t_mini *mini)
{
	if (mini->syn.backtick)
		ft_putstr_fd("does not support backtick\n", 2);
	if (mini->syn.here_string)
		ft_putstr_fd("does not support here_string\n", 2);
	if (mini->syn.background)
		ft_putstr_fd("does not support job control\n", 2);
	if (mini->syn.forced_output)
		ft_putstr_fd("does not support forced output redirection\n", 2);
	if (mini->syn.fd_dup)
		ft_putstr_fd("does not support file descriptor duplication\n", 2);
	if (mini->syn.input_sub)
		ft_putstr_fd("does not support process substitution for input\n", 2);
	if (mini->syn.output_sub)
		ft_putstr_fd("does not support process substitution for output\n", 2);
	if (mini->syn.backtick
		|| mini->syn.here_string || mini->syn.background
		|| mini->syn.forced_output || mini->syn.fd_dup
		|| mini->syn.input_sub || mini->syn.output_sub)
	{
		mini->syn.msg = 1;
		return (1);
	}
	return (0);
}
