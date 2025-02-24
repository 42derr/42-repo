/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputri-a <aputri-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:44:54 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 01:33:03 by aputri-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		else
			return (0);
	}
	return (1);
}

void	dup_back(t_mini *mini)
{
	if (dup2(mini->stdout, 1) == -1)
		clean_exit("dup2", mini);
	if (dup2(mini->stdin, 0) == -1)
		clean_exit("dup2", mini);
}

int	new_line(char ***envp, t_mini *mini)
{
	mini->cwd = alter_working_dir();
	if (!mini->cwd)
		clean_exit("malloc", mini);
	mini->input = readline(mini->cwd);
	free(mini->cwd);
	if (mini->input == NULL)
	{
		printf("exit\n");
		clean_exit(NULL, mini);
	}
	if (check_whitespace(mini->input))
		return (free(mini->input), 0);
	add_history(mini->input);
	mini->all_token = tokenization(mini->input, mini);
	if (syntax_check(mini) != 0)
		return (free_iteration(mini), 0);
	parsing(mini);
	if (hd_input(mini))
		return (mini->exit_status = 130, free_iteration(mini), 0);
	execute(mini->all_node, envp, mini);
	dup_back(mini);
	if (g_my_signal == SIGINT)
		printf("\n");
	return (free_iteration(mini), 0);
}
