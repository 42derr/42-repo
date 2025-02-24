/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:45:48 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:45:49 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_fork(pid_t *child, int pfd[2], t_mini *mini)
{
	*child = fork();
	if (*child == -1)
	{
		close(pfd[0]);
		close(pfd[1]);
		clean_exit("fork", mini);
	}
}

pid_t	create_pipe(t_node *node, char ***envp, t_mini *mini, int direc)
{
	pid_t	child;
	int		pfd[2];
	int		exit_stat;

	if (pipe(pfd) == -1)
		clean_exit("pipe", mini);
	create_fork(&child, pfd, mini);
	if (child == 0)
	{
		if (direc == 0)
		{
			if (dup2(pfd[1], 1) == -1)
				clean_exit("dup2", mini);
		}
		close(pfd[0]);
		close(pfd[1]);
		exit_stat = execute(node, envp, mini);
		clean_noexit(mini);
		exit (exit_stat);
	}
	if (dup2(pfd[0], 0) == -1)
		clean_exit("dup2", mini);
	close(pfd[1]);
	close(pfd[0]);
	return (child);
}
