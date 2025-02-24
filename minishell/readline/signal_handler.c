/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:45:08 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/18 17:11:42 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig)
{
	if (!sig)
		return ;
	printf("^C\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_my_signal = SIGINT;
	signal(SIGINT, handle_sigint);
}

void	heredoc_cmds_sigint(int sig)
{
	if (!sig)
		return ;
	printf("^C\n");
	g_my_signal = SIGINT;
}

void	cmds_sigint(int sig)
{
	if (!sig)
		return ;
	g_my_signal = SIGINT;
}

void	cmds_sigquit(int sig)
{
	if (!sig)
		return ;
	g_my_signal = SIGQUIT;
}
