/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:45:29 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/18 17:07:13 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_cmds(t_node *node, t_mini *mini)
{
	char	**args;

	node = build_in_temp(node, mini);
	if (!node)
		return (0);
	args = cmds_array(node->left, mini);
	g_my_signal = 0;
	if (build_in_handler(args, mini, node) != 0)
		return (mini->exit_status);
	return (run_command(args, mini, node));
}

int	execute_parenthesis(t_node *node, char ***envp, t_mini *mini)
{
	pid_t	child;
	int		save_exit;
	int		status;

	child = fork();
	if (child == -1)
		clean_exit("fork", mini);
	if (child == 0)
	{
		save_exit = run_action(mini, node->action, 0);
		if (save_exit == 0)
		{
			save_exit = execute(node->left, envp, mini);
			clean_noexit(mini);
			exit (save_exit);
		}
		clean_noexit(mini);
		exit (save_exit);
	}
	waitpid(child, &status, 0);
	run_command_status(status, mini, 0);
	return (mini->exit_status);
}
