/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:46:41 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:46:42 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	echo_newline(char *str)
{
	int	i;

	i = 1;
	if (str[0] && str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

int	run_echo(char **dir)
{
	int	no_newline;
	int	i;

	i = 1;
	no_newline = 0;
	while (dir[i] && echo_newline(dir[i]))
	{
		no_newline = 1;
		i++;
	}
	while (dir[i])
	{
		printf("%s", dir[i]);
		if (dir[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
