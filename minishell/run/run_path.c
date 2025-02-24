/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:45:44 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/18 16:18:40 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_handler(char ***dir, char *command)
{
	int		i;
	char	*path;

	i = 0;
	while ((*dir)[i])
	{
		path = final_path((*dir)[i], command);
		if (!path)
			return (ft_free_2d(dir), NULL);
		if (access(path, X_OK) == 0)
			return (ft_free_2d(dir), path);
		free(path);
		i++;
	}
	return (ft_free_2d(dir), NULL);
}

char	*find_full_path(char *command, t_mini *mini)
{
	char	*path;
	char	**dir;
	char	*name;

	name = ft_strdup("PATH");
	if (!name)
		clean_exit("malloc", mini);
	path = mygetenv(&name, mini);
	if (!path)
		return (free(name), NULL);
	free(name);
	dir = ft_split(path, ':');
	if (!dir)
		return (free(path), NULL);
	free(path);
	return (path_handler(&dir, command));
}

char	*final_path(char *dir, char *cmd)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;

	dir_len = (int)ft_strlen(dir);
	cmd_len = (int)ft_strlen(cmd);
	full_path = (char *) malloc (sizeof(char) * (dir_len + cmd_len + 2));
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	full_path[dir_len] = '/';
	ft_strcpy(full_path + dir_len + 1, cmd);
	return (full_path);
}
