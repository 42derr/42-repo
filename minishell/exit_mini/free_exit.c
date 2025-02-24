/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:49:06 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 05:26:30 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_temp(t_mini *mini)
{
	if (mini->temp_env)
		ft_lstclear(&mini->temp_env, &free);
	if (mini->temp_str)
	{
		free(mini->temp_str);
		mini->temp_str = NULL;
	}
	if (mini->temp_arr)
	{
		ft_free_2d(&mini->temp_arr);
		mini->temp_arr = NULL;
	}
}

void	clean_noexit(t_mini *mini)
{
	if (mini->stdin)
		close(mini->stdin);
	if (mini->stdout)
		close(mini->stdout);
	if (mini->new_shlvl)
	{
		free(mini->new_shlvl);
		mini->new_shlvl = NULL;
	}
	if (mini->envp)
	{
		ft_free_2d(&mini->envp);
		mini->envp = NULL;
	}
	if (mini->export_envp)
	{
		ft_free_2d(&mini->export_envp);
		mini->export_envp = NULL;
	}
	free_temp(mini);
	free_iteration(mini);
	rl_clear_history();
}

void	clean_exit(char *err, t_mini *mini)
{
	if (mini->temp_input)
	{
		free(mini->temp_input);
		mini->temp_input = NULL;
	}
	clean_noexit(mini);
	if (err)
		perror(err);
	exit (1);
}
