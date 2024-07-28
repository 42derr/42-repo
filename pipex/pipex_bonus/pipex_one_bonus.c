/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:03:01 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/25 16:53:06 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	doc_child(t_pipex *pipex, int fd[2], char *lim)
{
	char	*buffer;
	size_t	len;

	len = ft_strlen(lim);
	close (fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_handler("dup2", pipex);
	close (fd[1]);
	while (1)
	{
		buffer = get_next_line(0);
		if (!buffer)
			error_handler("get_next_line", pipex);
		if (ft_strncmp(buffer, lim, len) == 0 && buffer[len] == '\n')
			break ;
		ft_putstr_fd(buffer, STDOUT_FILENO);
		free(buffer);
	}
	free_pipex(pipex);
	free(buffer);
	exit(0);
}

void	handle_doc(char *lim, t_pipex *pipex)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		error_handler("pipe", pipex);
	pid = fork();
	if (pid == -1)
		error_handler("fork", pipex);
	if (pid == 0)
		doc_child(pipex, fd, lim);
	else
	{
		close (fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			error_handler("dup2", pipex);
		close (fd[0]);
	}
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	free(pipex->file1);
	free(pipex->file2);
	while (pipex->cmd[i])
	{
		free(pipex->cmd[i]);
		i++;
	}
	free(pipex->cmd);
}

void	free_array(char	**buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
}

void	error_handler(char *err, t_pipex *pipex)
{
	perror(err);
	free_pipex(pipex);
	exit (1);
}
