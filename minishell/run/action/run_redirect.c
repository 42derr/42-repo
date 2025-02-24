/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:46:20 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/18 18:10:05 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_redirect_input(char **file, int expand, t_mini *mini)
{
	int		fd;

	fd = open((*file), O_RDONLY);
	if (fd == -1)
	{
		perror((*file));
		if (expand == 1)
			free((*file));
		return (1);
	}
	if (expand == 1)
		free((*file));
	if (dup2(fd, 0) == -1)
		clean_exit("dup2", mini);
	close(fd);
	return (0);
}

int	run_redirect_output(char **file, int expand, t_mini *mini)
{
	int	fd;

	fd = open((*file), O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror((*file));
		if (expand == 1)
			free((*file));
		return (1);
	}
	if (expand == 1)
		free((*file));
	if (dup2(fd, 1) == -1)
		clean_exit("dup2", mini);
	close(fd);
	return (0);
}

int	run_append(char **file, int expand, t_mini *mini)
{
	int	fd;

	fd = open((*file), O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		perror((*file));
		if (expand == 1)
			free((*file));
		return (1);
	}
	if (expand == 1)
		free((*file));
	if (dup2(fd, 1) == -1)
		clean_exit("dup2", mini);
	close(fd);
	return (0);
}

int	handle_fail_open(int fd, char **file, int expand)
{
	if (fd == -1)
	{
		perror((*file));
		if (expand == 1)
			free((*file));
		return (1);
	}
	return (0);
}

int	run_redirect_io(char **file, int expand, t_mini *mini)
{
	int	fd;

	if (access((*file), F_OK) != 0)
	{
		fd = open((*file), O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
		{
			perror((*file));
			if (expand == 1)
				free((*file));
			return (1);
		}
		close(fd);
	}
	fd = open((*file), O_RDONLY);
	if (handle_fail_open(fd, file, expand))
		return (1);
	if (expand == 1)
		free((*file));
	if (dup2(fd, 0) == -1)
		clean_exit("dup2", mini);
	return (close(fd), 0);
}
