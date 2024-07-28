/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:04:37 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/25 17:35:40 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd, char **env, t_pipex *pipex)
{
	char		**args;
	char		*command;
	char		*full_path;

	args = ft_split(cmd, ' ');
	if (!args)
		error_handler("ft_split", pipex);
	command = args[0];
	if (ft_strchr(command, '/') != NULL)
	{
		full_path = command;
		if (access(command, X_OK) != 0)
		{
			free_array(args);
			error_handler("access", pipex);
		}
	}
	else
		full_path = find_full_path(command, env, pipex);
	if (!full_path)
		fullpath_error(command, pipex, args);
	execve(full_path, args, env);
	free(full_path);
	free_array(args);
	error_handler("execve", pipex);
}

char	*final_path(char *dir, char *cmd, t_pipex *pipex)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;

	dir_len = (int)ft_strlen(dir);
	cmd_len = (int)ft_strlen(cmd);
	full_path = (char *) malloc (sizeof(char) * (dir_len + cmd_len + 2));
	if (!full_path)
		error_handler("malloc", pipex);
	ft_strcpy(full_path, dir);
	full_path[dir_len] = '/';
	ft_strcpy(full_path + dir_len + 1, cmd);
	return (full_path);
}

char	*find_full_path(char *command, char **env, t_pipex *pipex)
{
	int			i;
	char		*path;
	char		**dir;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != 0)
			path = ft_strnstr(env[i], "PATH=", 5);
		i++;
	}
	dir = ft_split(path + 5, ':');
	if (!dir)
		return (NULL);
	i = 0;
	while (dir[i])
	{
		path = final_path(dir[i++], command, pipex);
		if (!path)
			return (free_array(dir), NULL);
		if (access(path, X_OK) == 0)
			return (free_array(dir), path);
		free(path);
	}
	return (free_array(dir), NULL);
}

void	free_special(t_pipex *pipex, char **args)
{
	free_pipex(pipex);
	free_array(args);
}

void	fullpath_error(char *command, t_pipex *pipex, char **args)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": Command not found\n", 2);
	free_special(pipex, args);
	exit (127);
}
