/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:47:01 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 05:24:07 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol_spes(char *nptr, t_mini *mini)
{
	long	s;
	int		i;
	int		m;

	i = 0;
	m = 1;
	s = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			m = m * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (m == 1 && (s > (LONG_MAX - (nptr[i] - '0')) / 10))
			mini->exit_max = 1;
		if (m == -1 && (s > (LONG_MAX - (nptr[i] - '0')) / 10))
			mini->exit_max = 1;
		s = s * 10 + (nptr[i] - '0');
		i++;
	}
	return (s * m);
}

int	call_run_exit(char **dir, t_mini *mini)
{
	int		argc;
	long	ret;

	mini->exit_max = 0;
	argc = 0;
	while (dir[argc])
		argc++;
	if (argc == 1)
		return (mini->exit = 1, 0);
	if (!is_number(dir[1]))
	{
		mini->exit = 2;
		return (mini->exit_temp = dir[1], 2);
	}
	if (argc == 2)
	{
		ret = ft_atol_spes(dir[1], mini) % 256;
		if (mini->exit_max == 1)
		{
			mini->exit = 2;
			return (mini->exit_temp = dir[1], 2);
		}
		return (mini->exit = 1, ret);
	}
	return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
}

int	run_exit(char **dir, t_mini *mini)
{
	int	exit_stat;

	exit_stat = call_run_exit(dir, mini);
	if (mini->exit)
	{
		mini->exit_status = exit_stat;
		exit_minishell(mini);
	}
	return (exit_stat);
}
