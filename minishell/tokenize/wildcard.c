/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:43:13 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:43:14 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_wc(char **arr)
{
	int		i;
	int		max;
	char	*temp;

	i = 0;
	max = ft_arrlen(arr);
	while (i < max - 1)
	{
		if (ft_strcmp(arr[i], arr[i + 1]) > 0)
		{
			temp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = temp;
			i = 0;
			continue ;
		}
		i++;
	}
}

int	read_dir_wildcard(DIR *dir, char *value, char ***args, int i)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.' && !match_wildcard(".*", value))
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_wildcard(value, entry->d_name))
		{
			(*args)[i] = ft_strdup(entry->d_name);
			if (!(*args)[i])
				return (1);
			i++;
		}
		entry = readdir(dir);
	}
	(*args)[i] = NULL;
	return (0);
}

char	**get_wildcard(char *value, int i)
{
	DIR				*dir;
	char			**args;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	args = (char **) malloc(sizeof(char *) * get_wildcard_size(value));
	if (!args)
		return (closedir(dir), NULL);
	if (read_dir_wildcard(dir, value, &args, i))
		return (closedir(dir), ft_free_2d(&args), NULL);
	sort_wc(args);
	return (closedir(dir), args);
}

int	match_wildcard(char *pattern, char *str)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (1);
			while (*str)
			{
				if (match_wildcard(pattern, str))
					return (1);
				str++;
			}
			return (0);
		}
		else if (*pattern == *str || *pattern == '?')
		{
			pattern++;
			str++;
		}
		else
			return (0);
	}
	return (!*str);
}

int	get_wildcard_size(char *value)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	i = 0;
	dir = opendir(".");
	if (!dir)
		return (-1);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.' && !match_wildcard(".*", value))
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_wildcard(value, entry->d_name))
			i++;
		entry = readdir(dir);
	}
	return (closedir(dir), i + 1);
}
