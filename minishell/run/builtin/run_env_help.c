/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:46:55 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/18 17:07:39 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*env_exit_stat(char *str, int len, t_mini *mini)
{
	char	*env_value;

	if (str[len] == '?')
	{
		if (g_my_signal == SIGINT)
			env_value = ft_itoa(130);
		else
			env_value = ft_itoa(mini->exit_status);
		if (!env_value)
			clean_exit("malloc", mini);
		return (env_value);
	}
	return (NULL);
}
