/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:47:33 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:47:34 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_env_smart_check(int c)
{
	if (c && c != '$'
		&& (ft_isalpha(c) || c == '_' || ft_isdigit(c)))
		return (1);
	return (0);
}

int	get_env_check(int c, int cn, int sq, int dq)
{
	if ((dq || (!sq && !dq))
		&& c == '$'
		&& (ft_isalpha(cn)
			|| cn == '_'
			|| ft_isdigit(cn)
			|| cn == '?'))
		return (1);
	return (0);
}

int	get_env_len(char *str, t_mini *mini, int sq, int dq)
{
	char	*env_string;
	int		counter;
	int		i;

	i = 0;
	counter = 0;
	while (str[i])
	{
		single_double(str, i, &dq, &dq);
		if (get_env_check(str[i], str[i + 1], sq, dq))
		{
			i++;
			env_string = get_env_smart(str + i, mini, 0, 0);
			while (get_env_smart_check(str[i]))
				i++;
			if (!env_string)
				continue ;
			counter += ft_strlen(env_string);
			free(env_string);
			continue ;
		}
		counter++;
		i++;
	}
	return (counter);
}

char	*expand_env(char *str, t_mini *mini, int sq, int dq)
{
	char	*new_str;
	int		i;
	int		j;
	char	*env_string;

	malloc_expand(&new_str, str, mini);
	j = 0;
	i = 0;
	while (str[i])
	{
		single_double(str, i, &sq, &dq);
		if (get_env_check(str[i], str[i + 1], sq, dq))
		{
			expand_env_helper(str, &i, mini, &env_string);
			if (!env_string)
				continue ;
			ft_memcpy(new_str + j, env_string, ft_strlen(env_string));
			j += ft_strlen(env_string);
			free(env_string);
			continue ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (mini->temp_str = NULL, new_str);
}

void	expand_env_helper(char *str, int *i, t_mini *mini, char **env_string)
{
	(*i)++;
	(*env_string) = get_env_smart(str + *i, mini, 0, 0);
	if (str[*i] == '?')
		(*i)++;
	while (get_env_smart_check(str[*i]))
		(*i)++;
}
