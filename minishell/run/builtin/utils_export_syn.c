/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_syn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputri-a <aputri-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:48:01 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 01:15:40 by aputri-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	syntax_new(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == '`' || str[i] == '\"' || str[i] == '$')
			c += 2;
		else
			c++;
		i++;
	}
	return (c);
}

char	*fix_syntax_new(char *str, t_mini *mini)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * syntax_new(str) + 3);
	if (!new)
		clean_exit ("malloc", mini);
	if (str && !(ft_isalpha(str[0]) || str[0] == '_'))
		return (ft_print_errs("export: `", str,
				"': not a valid identifier", NULL),
			free(new), NULL);
	while (str[i] && str[i] != '=')
	{
		if (str && (ft_isalpha(str[i]) || str[i] == '_' || ft_isdigit(str[i])))
			new[j++] = str[i++];
		else
			return (ft_print_errs("export: `", str,
					"': not a valid identifier\n", NULL), free(new), NULL);
	}
	if (!str[i])
		return (new[j] = '\0', new);
	fix_syntax_help(str, &new, i, j);
	return (new);
}

void	fix_syntax_help(char *str, char **new, int i, int j)
{
	(*new)[j++] = str[i++];
	(*new)[j++] = '\"';
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == '`' || str[i] == '\"' || str[i] == '$')
			(*new)[j++] = '\\';
		(*new)[j++] = str[i++];
	}
	(*new)[j++] = '\"';
	(*new)[j] = '\0';
}

void	single_double(char *str, int i, int *sq, int *dq)
{
	if (str[i] == '\'' && !(*dq))
		(*sq) = !(*sq);
	if (str[i] == '\"' && !(*sq))
		(*dq) = !(*dq);
}
