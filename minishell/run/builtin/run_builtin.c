/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:46:31 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:46:32 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	run_builtin(char **args, t_mini *mini)
	{
	if (args[0] && ft_strcmp(args[0], "pwd") == 0)
		mini->exit_status = (run_pwd());
	if (args[0] && ft_strcmp(args[0], "cd") == 0)
		mini->exit_status = run_cd(args, mini, 0);
	if (args[0] && ft_strcmp(args[0], "echo") == 0)
		mini->exit_status = run_echo(args);
	if (args[0] && ft_strcmp(args[0], "exit") == 0)
		mini->exit_status = run_exit(args, mini);
	if (args[0] && ft_strcmp(args[0], "export") == 0)
		mini->exit_status = run_export(args, mini);
	if (args[0] && ft_strcmp(args[0], "env") == 0)
		mini->exit_status = run_env(args, mini);
	if (args[0] && ft_strcmp(args[0], "unset") == 0)
		mini->exit_status = run_unset(args, mini);
}
