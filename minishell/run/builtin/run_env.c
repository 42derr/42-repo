/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputri-a <aputri-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:46:50 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 00:53:26 by aputri-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_env(char **dir, t_mini *mini)
{
	int	max;

	max = 0;
	while (dir[max])
		max++;
	if (max == 1)
		return (print_export_env(mini, 1), 0);
	return (ft_putstr_fd("Minishell env dont accept args\n", 2), 1);
}

void	edit_env(char *new_str, t_mini *mini)
{
	char	**env;
	int		i;
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
				env[i] = ft_strdup(new_str);
				if (!env[i])
					clean_exit("malloc", mini);
				return ;
			}
		}
		i++;
	}
	sync_env(new_str, mini);
}

void	sync_env(char *new_str, t_mini *mini)
{
	int		i;
	char	**temp;
	char	**env;

	env = mini->envp;
	i = 0;
	while (env[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 2));
	if (!temp)
		clean_exit("malloc", mini);
	i = 0;
	while (env[i])
	{
		temp[i] = ft_strdup(env[i]);
		if (!temp[i])
			free_array_exit(&temp, mini);
		i++;
	}
	temp[i] = ft_strdup(new_str);
	if (!temp[i])
		free_array_exit(&temp, mini);
	temp[i + 1] = NULL;
	ft_free_2d(&mini->envp);
	mini->envp = temp;
}

char	*get_env_smart(char *str, t_mini *mini, int i, int len)
{
	char	*env_name;
	char	*env_value;

	env_value = env_exit_stat(str, len, mini);
	if (env_value)
		return (env_value);
	while (get_env_smart_check(str[len]))
		len++;
	env_name = malloc(sizeof(char) * len + 1);
	if (!env_name)
		clean_exit("malloc", mini);
	len = 0;
	if (str[0] && ft_isdigit(str[0]))
		len++;
	while (get_env_smart_check(str[len]))
		env_name[i++] = str[len++];
	env_name[i] = '\0';
	if (str[0] && ft_isdigit(str[0]))
		return (env_name);
	env_value = mygetenv(&env_name, mini);
	if (!env_value)
		env_value = search_temp(&env_name, mini);
	free(env_name);
	return (env_value);
}

char	*mygetenv(char **name, t_mini *mini)
{
	char	**env;
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(*name);
	env = mini->envp;
	while (env[i])
	{
		if (ft_strncmp(env[i], *name, len) == 0
			&& env[i][len] == '=')
		{
			str = ft_strdup(env[i] + len + 1);
			if (!str)
				free_str_exit(name, mini);
			return (str);
		}
		i++;
	}
	return (NULL);
}
