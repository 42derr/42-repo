/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:47:20 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:47:21 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset_temp_env(char *str, t_mini *mini)
{
	t_list	*save;
	t_list	*prev;
	int		str_len;

	save = mini->temp_env;
	prev = NULL;
	str_len = ft_strlen(str);
	while (save)
	{
		if (ft_strncmp((char *)save->content, str, str_len) == 0
			&& ((char *)save->content)[str_len] == '=')
		{
			if (prev == NULL)
				mini->temp_env = save->next;
			else
				prev->next = save->next;
			ft_lstdelone(save, &free);
			return ;
		}
		prev = save;
		save = save->next;
	}
}

int	run_unset(char **dir, t_mini *mini)
{
	int	max;
	int	i;

	i = 1;
	max = 0;
	while (dir[max])
		max++;
	if (max == 1)
		return (1);
	while (i < max)
	{
		if (ft_strchr(dir[i], '='))
		{
			i++;
			continue ;
		}
		unset_temp_env(dir[i], mini);
		unset_export_env(dir[i], mini);
		unset_real_env(dir[i], mini);
		i++;
	}
	return (0);
}

void	unset_export_env(char *new_str, t_mini *mini)
{
	int		i;
	char	**env;
	int		len;

	env = mini->export_envp;
	i = 0;
	while (env[i])
	{
		len = ft_strlen(new_str);
		if (ft_strncmp(env[i], new_str, len) == 0)
		{
			if (env[i][len] == '=' || env[i][len] == '\0')
			{
				free(env[i]);
				while (env[i])
				{
					env[i] = env[i + 1];
					i++;
				}
				return ;
			}
		}
		i++;
	}
}

void	unset_real_env(char *new_str, t_mini *mini)
{
	int		i;
	char	**env;
	int		len;

	env = mini->envp;
	i = 0;
	while (env[i])
	{
		len = ft_strchr(env[i], '=') - env[i];
		if ((ft_strncmp(env[i], new_str, len) == 0))
		{
			if (env[i][len] == '=')
			{
				free(env[i]);
				while (env[i])
				{
					env[i] = env[i + 1];
					i++;
				}
				return ;
			}
		}
		i++;
	}
}
