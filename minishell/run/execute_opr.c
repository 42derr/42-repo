/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_opr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:45:34 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:45:35 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_or(t_node *node, char ***envp, t_mini *mini)
{
	if (execute(node->left, envp, mini) != 0)
		return (execute(node->right, envp, mini));
	return (0);
}

int	execute_and(t_node *node, char ***envp, t_mini *mini)
{
	int	save_exit;

	save_exit = execute(node->left, envp, mini);
	if (save_exit == 0)
		return (execute(node->right, envp, mini));
	return (1);
}

int	execute_pipe(t_node *node, char ***envp, t_mini *mini)
{
	int		status;
	pid_t	left;
	pid_t	right;

	mini->left = create_pipe(node->left, envp, mini, 0);
	left = mini->left;
	mini->right = create_pipe(node->right, envp, mini, 1);
	right = mini->right;
	signal(SIGINT, cmds_sigint);
	waitpid(left, &status, 0);
	run_command_status(status, mini, 0);
	waitpid(right, &status, 0);
	run_command_status(status, mini, 0);
	if (dup2(mini->stdin, 0) == -1)
		clean_exit("dup2", mini);
	return (mini->exit_status);
}
