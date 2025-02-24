/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:47:28 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/18 14:57:24 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	build_in_handler(char **args, t_mini *mini, t_node *node)
{
	int		build_in;
	int		save_exit;

	build_in = 0;
	if (args[0] && (ft_strcmp(args[0], "pwd") == 0
			|| ft_strcmp(args[0], "cd") == 0
			|| ft_strcmp(args[0], "echo") == 0
			|| ft_strcmp(args[0], "exit") == 0
			|| ft_strcmp(args[0], "export") == 0
			|| ft_strcmp(args[0], "env") == 0
			|| ft_strcmp(args[0], "unset") == 0))
		build_in = 1;
	if (build_in != 1)
		return (0);
	save_exit = run_action(mini, node->action, 0);
	if (save_exit != 0)
		return (mini->exit_status = save_exit, -1);
	run_builtin(args, mini);
	return (build_in);
}

int	check_build_temp(char *str, t_mini *mini)
{
	char	*new;
	char	*old;
	int		i;

	old = NULL;
	if (!ft_strchr(str, '='))
		return (1);
	if (ft_strchr(str, '$'))
		old = expand_env(str, mini, 0, 0);
	handle_old_temp(&new, mini, &old, str);
	if (new && !(ft_isalpha(new[0]) || new[0] == '_'))
		return (free(new), 1);
	i = 0;
	while (new && new[i] != '=')
	{
		if (new && !(ft_isalpha(new[i]) || new[i] == '_' || ft_isdigit(new[i])))
			return (free(new), 1);
		i++;
	}
	return (free(new), 0);
}

t_node	*build_in_temp(t_node *node, t_mini *mini)
{
	t_node	*temp;

	temp = node->left;
	if (node->left && ft_strchr(node->left->token->value, '='))
	{
		mini->exit_status = 0;
		while (node->left)
		{
			if (check_build_temp(node->left->token->value, mini))
				return (node);
			node = node->left;
		}
		while (temp)
		{
			handle_temp_env(temp->token->value, mini);
			temp = temp->left;
		}
		return (NULL);
	}
	return (node);
}

char	*ft_trim_quoted(char *str, int sq, int dq, t_mini *mini)
{
	char	*new_str;
	int		i;

	mini->temp = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		clean_exit("malloc", mini);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !dq)
		{
			sq = !sq;
			i++;
			continue ;
		}
		if (str[i] == '\"' && !sq)
		{
			dq = !dq;
			i++;
			continue ;
		}
		new_str[mini->temp++] = str[i++];
	}
	return (new_str[mini->temp] = '\0', new_str);
}
