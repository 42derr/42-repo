/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:42:56 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:42:57 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cmds_handler(char *arg)
{
	char	**cmds;
	char	*store;
	int		i;

	i = 0;
	store = arg;
	cmds = malloc(sizeof(char *) * (get_cmd_array_size(store)));
	if (!cmds)
		return (NULL);
	while (*arg)
	{
		while (*arg && ft_is_whitespace(*arg))
			arg++;
		if (*arg && !ft_is_whitespace(*arg))
		{
			cmds[i] = fill_cmd(&arg, 0, 0, 0);
			if (!cmds[i])
				return (ft_free_2d(&cmds), ft_error_exit("malloc"), NULL);
			i++;
		}
	}
	return (cmds[i] = NULL, cmds);
}

char	*fill_cmd(char **arg, int sq, int dq, int bt)
{
	char	*arr;
	char	*store;
	int		i;
	int		j;

	j = 0;
	store = *arg;
	arr = malloc(sizeof(char) * (get_cmd_size(&store, 0, 0, 0)));
	if (!arr)
		return (NULL);
	i = find_cmd_token(arg);
	if (i != 0)
	{
		while (j < i)
			arr[j++] = (*(*arg)++);
		return (arr[j] = '\0', arr);
	}
	while ((**arg) && (!ft_is_whitespace(**arg) || sq || dq || bt))
	{
		if (!sq && !dq && !bt && find_cmd_token(arg))
			break ;
		cmd_quote_check(arg, &sq, &dq, &bt);
		arr[j++] = (*(*arg)++);
	}
	return (arr[j] = '\0', arr);
}

int	find_cmd_token(char **arg)
{
	if (ft_strncmp(*arg, "<<<", 3) == 0)
		return (3);
	if (ft_strncmp(*arg, "&&", 2) == 0
		|| ft_strncmp(*arg, "||", 2) == 0
		|| ft_strncmp(*arg, "<(", 2) == 0
		|| ft_strncmp(*arg, ">(", 2) == 0
		|| ft_strncmp(*arg, "<<", 2) == 0
		|| ft_strncmp(*arg, ">>", 2) == 0
		|| ft_strncmp(*arg, ">|", 2) == 0
		|| ft_strncmp(*arg, ">&", 2) == 0
		|| ft_strncmp(*arg, "<&", 2) == 0
		|| ft_strncmp(*arg, "<>", 2) == 0)
	{
		return (2);
	}
	if ((**arg) == '(' || (**arg) == ')'
		|| (**arg) == '<' || (**arg) == '>'
		|| (**arg) == '|' || (**arg) == '&')
	{
		return (1);
	}
	return (0);
}

void	cmd_quote_check(char **arg, int *sq, int *dq, int *bt)
{
	if (!(*bt) && !(*dq) && (**arg) == '\'')
		(*sq) = !(*sq);
	else if (!(*bt) && !(*sq) && (**arg) == '"')
		(*dq) = !(*dq);
	else if (!sq && (**arg) == '`')
		(*bt) = !(*bt);
}
