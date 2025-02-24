/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_token_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:44:28 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:44:29 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_is_open_parenthesis(t_token token, t_mini *mini)
{
	if (mini->syn.i < 0)
		return (0);
	unsupported_check(token, mini);
	return (token.type == LEFT_PARENTHESIS
		|| token.type == INPUT_SUBSTITUTE
		|| token.type == OUTPUT_SUBSTITUTE);
}

int	token_is_operator(t_token token, t_mini *mini)
{
	if (mini->syn.i < 0)
		return (0);
	unsupported_check(token, mini);
	return (token.type == AND || token.type == OR || token.type == PIPE);
}

int	token_is_redirect(t_token token, t_mini *mini)
{
	if (mini->syn.i < 0)
		return (0);
	unsupported_check(token, mini);
	return (token.type == REDIRECT_INPUT
		|| token.type == REDIRECT_OUTPUT
		|| token.type == REDIRECT_IO
		|| token.type == HERE_DOC
		|| token.type == APPEND
		|| token.type == HERE_STRING
		|| token.type == FORCED_OUTPUT
		|| token.type == FD_DUP);
}

int	token_is_cmd(t_token token, t_mini *mini)
{
	if (mini->syn.i < 0)
		return (0);
	unsupported_check(token, mini);
	return (token.type == SINGLE_QUOTE
		|| token.type == DOUBLE_QUOTE
		|| token.type == BACKTICK
		|| token.type == EXIT_STATUS
		|| token.type == ENV_VAR
		|| token.type == WILDCARD
		|| token.type == CMDS
		|| token.type == ARGS);
}

void	unsupported_check(t_token token, t_mini *mini)
{
	if (token.type == BACKTICK)
		mini->syn.backtick = 1;
	if (token.type == HERE_STRING)
		mini->syn.here_string = 1;
	if (token.type == BACKGROUND)
		mini->syn.background = 1;
	if (token.type == FORCED_OUTPUT)
		mini->syn.forced_output = 1;
	if (token.type == FD_DUP)
		mini->syn.fd_dup = 1;
	if (token.type == INPUT_SUBSTITUTE)
		mini->syn.input_sub = 1;
	if (token.type == OUTPUT_SUBSTITUTE)
		mini->syn.output_sub = 1;
}
