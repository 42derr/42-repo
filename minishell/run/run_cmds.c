/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:45:39 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 05:23:37 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_not_found(char *str, t_mini *mini)
{
	struct stat	statbuf;

	if (str && ft_strchr(str, '/'))
	{
		if (stat(str, &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
				ft_print_errs("Minishell: ", str, ": Is a ", "directory");
			else if (S_ISREG(statbuf.st_mode) && !(statbuf.st_mode & S_IXUSR))
				ft_print_errs("Minishell: ", str, ": Permission ", "denied");
			clean_noexit(mini);
			exit(126);
		}
		else
			ft_print_errs("Minishell: ", str,
				": No such ", "file or directory");
	}
	else if (str)
		ft_print_errs(str, ": command not found", NULL, NULL);
	clean_noexit(mini);
	exit(127);
}

int	run_command(char **args, t_mini *mini, t_node *node)
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
		if (save_exit)
			clean_exit(NULL, mini);
		exec_cmd(args, mini);
		if (dup2(mini->stdout, 1) == -1)
			clean_exit("dup2", mini);
		handle_not_found(args[0], mini);
	}
	signal(SIGQUIT, cmds_sigquit);
	signal(SIGINT, cmds_sigint);
	waitpid(child, &status, 0);
	run_command_status(status, mini, child);
	return (mini->exit_status);
}

void	clean_fd(t_mini *mini)
{
	int	i;

	close(mini->stdin);
	mini->stdin = 0;
	close(mini->stdout);
	mini->stdout = 0;
	i = 0;
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
}

void	exec_cmd(char **args, t_mini *mini)
{
	char		*command;
	char		*full_path;

	command = args[0];
	if (!command)
	{
		clean_noexit(mini);
		exit (0);
	}
	if (ft_strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) != 0)
			return ;
		full_path = ft_strdup(command);
		if (!full_path)
			clean_exit("malloc", mini);
	}
	else
		full_path = find_full_path(command, mini);
	if (!full_path)
		return ;
	clean_fd(mini);
	execve(full_path, args, mini->envp);
	free(full_path);
}
