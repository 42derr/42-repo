/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:47:04 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:47:06 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_export(char **dir, t_mini *mini)
{
	int	max;
	int	i;
	int	exit_stat;

	exit_stat = 0;
	i = 1;
	max = 0;
	while (dir[max])
		max++;
	if (max == 1)
		print_export_env(mini, 0);
	while (i < max)
	{
		exit_stat = append_export(dir[i], mini, 0);
		i++;
	}
	return (exit_stat);
}

void	print_export_env(t_mini *mini, int type)
{
	char	**env;
	int		i;

	if (type == 0)
		env = mini->export_envp;
	else
		env = mini->envp;
	sort_export(&env);
	i = 0;
	while (env[i])
	{
		if (type == 0)
		{
			if (ft_strcmp(env[i], "_=\"./minishell\"") != 0)
			{
				printf("declare -x ");
				printf("%s\n", env[i]);
			}
		}
		else
			printf("%s\n", env[i]);
		i++;
	}
}

void	sort_export(char ***env)
{
	int		i;
	int		max;
	char	*temp;

	i = 0;
	max = 0;
	while ((*env)[max])
		max++;
	while (i < max - 1)
	{
		if (ft_strcmp((*env)[i], (*env)[i + 1]) > 0)
		{
			temp = (*env)[i];
			(*env)[i] = (*env)[i + 1];
			(*env)[i + 1] = temp;
			i = 0;
			continue ;
		}
		i++;
	}
}

char	*fix_syntax_string(char *str)
{
	char	*new_str;
	int		len;
	int		equal_pos;
	int		i;
	int		j;

	len = ft_strlen(str);
	equal_pos = ft_strchr(str, '=') - str;
	new_str = malloc(sizeof(char) * len + 3);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str, equal_pos + 1);
	i = equal_pos + 1;
	j = equal_pos + 1;
	new_str[i++] = '\"';
	while (str[j])
		new_str[i++] = str[j++];
	new_str[i++] = '\"';
	new_str[i] = '\0';
	return (new_str);
}

char	**fix_syntax(char **env)
{
	char	**new_buffer;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_buffer = malloc(sizeof(char *) * (i + 1));
	if (!new_buffer)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_buffer[i] = fix_syntax_string(env[i]);
		if (!new_buffer[i])
		{
			ft_free_2d(&new_buffer);
			return (NULL);
		}
		i++;
	}
	new_buffer[i] = NULL;
	return (new_buffer);
}
