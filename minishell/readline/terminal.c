/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:19:34 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/18 15:19:35 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	disable_echo(t_mini *mini)
{
	struct termios	term;

	if (!mini)
		return ;
	if (tcgetattr(STDIN_FILENO, &mini->orig_termios) == -1)
	{
		perror("tcgetattr");
		exit(1);
	}
	term = mini->orig_termios;
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}

void	restore_terminal(t_mini *mini)
{
	if (!mini)
		return ;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &mini->orig_termios) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}
