/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_sigc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:19:51 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/18 15:19:53 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_sigc(t_mini *mini, pid_t child_pid)
{
	if (g_my_signal == SIGINT)
	{
		mini->sigc = 130;
		g_my_signal = 0;
		kill(child_pid, SIGKILL);
	}
}
