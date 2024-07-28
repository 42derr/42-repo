/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:22:09 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/25 17:24:01 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	read_open(t_pipex *pipex, char *buffer)
{
	int	fd;
	int	bytes;

	fd = open(pipex->file1, O_RDONLY);
	if (fd == -1)
		return (0);
	bytes = read(fd, buffer, sizeof(buffer));
	if (bytes == -1)
	{
		close (fd);
		error_handler("read", pipex);
	}
	close (fd);
	return (bytes);
}

void	is_loop(t_pipex *pipex)
{
	char	buffer1[100];
	char	buffer2[100];
	int		bytes;

	bytes = read_open(pipex, buffer1);
	if (!bytes)
		return ;
	bytes = read_open(pipex, buffer2);
	if (!bytes)
		return ;
	if (ft_memcmp(buffer1, buffer2, bytes) != 0)
		pipex->loop = 1;
}
