/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputri-a <aputri-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:46:36 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 00:32:01 by aputri-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_cd(char **dir, t_mini *mini, int i)
{
	char	*env;
	char	*name;

	while (dir[i])
		i++;
	if (i == 1)
	{
		name = ft_strdup("HOME");
		if (!name)
			clean_exit("malloc", mini);
		env = mygetenv(&name, mini);
		if (!env)
			return (free(name), ft_putstr_fd("cd: HOME not set\n", 2), 1);
		free(name);
		if (chdir(env) != 0)
			return (ft_print_errs("cd: ", env, ": ", strerror(errno)),
				free(env), 1);
		free(env);
		return (0);
	}
	if (i > 2)
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	if (chdir(dir[1]) != 0)
		return (ft_print_errs("cd: ", dir[1], ": ", strerror(errno)), 1);
	return (0);
}
