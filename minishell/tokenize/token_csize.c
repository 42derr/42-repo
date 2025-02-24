/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_csize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:43:02 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:43:03 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_cmd_array_size(char *arg)
{
	int	i;

	i = 0;
	while (*arg)
	{
		while (*arg && ft_is_whitespace(*arg))
			arg++;
		if (*arg && !ft_is_whitespace(*arg))
			i++;
		get_cmd_size(&arg, 0, 0, 0);
	}
	return (i + 1);
}

int	get_cmd_size(char **arg, int sq, int dq, int bt)
{
	int		i;

	i = find_cmd_token(arg);
	if (i != 0)
	{
		while (sq++ < i)
			(*arg)++;
		return (i + 1);
	}
	while ((**arg) && (!ft_is_whitespace(**arg) || sq || dq || bt))
	{
		if (!sq && !dq && !bt && find_cmd_token(arg))
			break ;
		if (!bt && !dq && (**arg) == '\'')
			sq = !sq;
		else if (!bt && !sq && (**arg) == '"')
			dq = !dq;
		else if (!sq && !dq && (**arg) == '`')
			bt = !bt;
		(*arg)++;
		i++;
	}
	return (i + 1);
}
