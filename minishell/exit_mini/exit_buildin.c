/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputri-a <aputri-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:48:59 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 01:32:45 by aputri-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_minishell(t_mini *mini)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		printf("exit\n");
	if (mini->exit == 2)
		ft_print_errs("exit: ", mini->exit_temp,
			": numeric argument required", NULL);
	clean_noexit(mini);
	exit (mini->exit_status);
}
