/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:47:41 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:47:41 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	dup_export(char **env, char ***temp, int *i, t_mini *mini)
{
	while (env[*i])
	{
		(*temp)[*i] = ft_strdup(env[*i]);
		if (!(*temp)[*i])
			free_array_exit(temp, mini);
		(*i)++;
	}
}

int	append_export(char *new_str, t_mini *mini, int i)
{
	char	**env;
	char	**temp;

	env = mini->export_envp;
	if (check_duplicate(new_str, mini))
		return (0);
	temp = malloc(sizeof(char *) * (ft_arrlen(env) + 2));
	if (!temp)
		clean_exit("malloc", mini);
	mini->temp_arr = temp;
	i = 0;
	dup_export(env, &temp, &i, mini);
	if (check_temp_env(new_str, mini, &temp, i))
		return (mini->temp_arr = NULL, 0);
	temp[i] = fix_syntax_new(new_str, mini);
	if (!temp[i])
		return (mini->temp_arr = NULL, ft_free_2d(&temp), 1);
	temp[i + 1] = NULL;
	if (ft_strchr(new_str, '='))
		sync_env(new_str, mini);
	ft_free_2d(&mini->export_envp);
	mini->temp_arr = NULL;
	return (mini->export_envp = temp, 0);
}

int	edit_export(char *new_str, char **old_str, t_mini *mini)
{
	char	*fix_new_str;

	fix_new_str = fix_syntax_new(new_str, mini);
	if (!fix_new_str)
		return (1);
	if (ft_strcmp(fix_new_str, *old_str) == 0)
		return (free(fix_new_str), 1);
	free(*old_str);
	*old_str = fix_new_str;
	return (0);
}

int	check_duplicate(char *new_str, t_mini *mini)
{
	char	**envp;
	int		len;
	int		i;

	i = 0;
	envp = mini->export_envp;
	while (envp[i])
	{
		len = ft_strlen(envp[i]);
		if (ft_strchr(envp[i], '='))
			len = ft_strchr(envp[i], '=') - envp[i];
		if (ft_strncmp(envp[i], new_str, len) == 0)
		{
			if (new_str[len] == '=')
			{
				if (edit_export(new_str, &envp[i], mini))
					return (1);
				return (edit_env(new_str, mini), 1);
			}
			else if (new_str[len] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	is_in_export(char *str, t_mini *mini)
{
	int		len;
	int		i;
	char	**env;

	len = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
	i = 0;
	env = mini->export_envp;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0
			&& (env[i][len] == '=' || env[i][len] == '\0'))
			return (1);
		i++;
	}
	return (0);
}
