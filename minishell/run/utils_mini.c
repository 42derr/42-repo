/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:46:01 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:46:02 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array_exit(char ***arr, t_mini *mini)
{
	ft_free_2d(arr);
	clean_exit("malloc", mini);
}

void	free_str_exit(char **str, t_mini *mini)
{
	free(*str);
	clean_exit("malloc", mini);
}

int	count_spaces(char *str, t_mini *mini)
{
	int		count;
	int		in_space;
	char	*temp;

	temp = expand_env(str, mini, 0, 0);
	str = temp;
	count = 0;
	in_space = 0;
	while (*str != '\0')
	{
		if (*str == ' ')
		{
			if (!in_space)
			{
				count++;
				in_space = 1;
			}
		}
		else
			in_space = 0;
		str++;
	}
	return (free(temp), count);
}

int	get_num_command(t_node *final, t_mini *mini)
{
	int		i;
	int		j;
	t_node	*store;

	store = final;
	i = 0;
	while (store)
	{
		if (store->token->type != CMDS)
		{
			if (store->token->type == WILDCARD)
			{
				j = 0;
				while (store->token->wild[j++])
					i++;
			}
			if (store->token->value && ft_strchr(store->token->value, '$'))
				i += count_spaces(store->token->value, mini) + 1;
			i++;
		}
		store = store->left;
	}
	return (i);
}
