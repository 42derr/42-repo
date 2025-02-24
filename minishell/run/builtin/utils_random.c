/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_random.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:48:05 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 05:32:16 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	malloc_expand(char **new_str, char *str, t_mini *mini)
{
	*new_str = malloc (sizeof(char *) * (get_env_len(str, mini, 0, 0) + 1));
	if (!*new_str)
		clean_exit("malloc", mini);
	if (mini->temp_str)
		free(mini->temp_str);
	mini->temp_str = *new_str;
}

void	ft_print_errs(char *stra, char *strb, char *strc, char *strd)
{
	if (stra)
		ft_putstr_fd(stra, 2);
	if (strb)
		ft_putstr_fd(strb, 2);
	if (strc)
		ft_putstr_fd(strc, 2);
	if (strd)
		ft_putstr_fd(strd, 2);
	ft_putstr_fd("\n", 2);
}

void	run_command_status(int status, t_mini *mini, pid_t child)
{
	if (g_my_signal == SIGQUIT)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			ft_putstr_fd("Quit (core dumped)\n", 2);
		if (child)
			kill(child, SIGKILL);
		mini->exit_status = 131;
	}
	else if (g_my_signal == SIGINT)
		mini->exit_status = 130;
	else if (WIFEXITED(status))
		mini->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		mini->exit_status = 128 + WTERMSIG(status);
	else
		mini->exit_status = -1;
}
