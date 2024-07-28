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

#include "pipex.h"

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
