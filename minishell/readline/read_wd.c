/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_wd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:44:59 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 05:34:19 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*alter_working_dir(void)
{
	char	**path;
	int		max;
	char	cwd[1024];
	char	*full_path;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	path = ft_split(cwd, '/');
	if (!path)
		return (NULL);
	max = ft_arrlen(path);
	if (max == 0)
		return (ft_free_2d(&path), ft_strdup("😺:/$ "));
	else
	{
		if (alter_wd_helper(max, &full_path, 0, path))
			return (ft_free_2d(&path), NULL);
	}
	return (ft_free_2d(&path), full_path);
}

int	set_full_path(int max, char **path, char **full_path, int *i)
{
	if (max >= 2 && ft_strncmp(path[0], "home", 5) == 0)
	{
		*full_path = ft_strdup("😺:~");
		if (!(*full_path))
			return (1);
		*i = 2;
	}
	else
	{
		*full_path = ft_strdup("😺:");
		if (!(*full_path))
			return (1);
		*i = 0;
	}
	return (0);
}

int	alter_wd_helper(int max, char **full_path, int i, char **path)
{
	char	*new_path;

	if (set_full_path(max, path, full_path, &i))
		return (1);
	while (path[i])
	{
		new_path = ft_strjoin(*full_path, "/");
		free(*full_path);
		if (!new_path)
			return (1);
		*full_path = new_path;
		new_path = ft_strjoin(*full_path, path[i]);
		free(*full_path);
		if (!new_path)
			return (1);
		*full_path = new_path;
		i++;
	}
	new_path = ft_strjoin(*full_path, "$ ");
	free(*full_path);
	if (!new_path)
		return (1);
	*full_path = new_path;
	return (0);
}
