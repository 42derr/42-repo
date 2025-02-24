/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:44:47 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:44:49 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_mini(t_mini *mini, char ***envp)
{
	mini->stdout = dup(1);
	if (mini->stdout == -1)
		clean_exit("dup", mini);
	mini->stdin = dup(0);
	if (mini->stdin == -1)
		clean_exit("dup", mini);
	if (!(*envp) || !(*envp)[0])
	{
		mini->envp = make_default_env();
		if (!mini->envp)
			clean_exit("malloc", mini);
	}
	else
	{
		if (update_shlvl(envp, 0, 0, mini))
			clean_exit("malloc", mini);
		mini->envp = init_envp(*envp);
		if (!mini->envp)
			clean_exit("malloc", mini);
	}
	mini->export_envp = fix_syntax(mini->envp);
	if (!mini->export_envp)
		clean_exit("malloc", mini);
	mini->cmds = NULL;
}

char	**init_envp(char **envp)
{
	char	*shlvl_str;
	char	**new_envp;
	int		i;

	shlvl_str = getenv("SHLVL");
	if (shlvl_str)
		return (ft_copy_arr(envp));
	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc (sizeof(char *) * (i + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			return (ft_free_2d(&new_envp), NULL);
		i++;
	}
	new_envp[i++] = ft_strdup("SHLVL=1");
	new_envp[i] = NULL;
	return (new_envp);
}
