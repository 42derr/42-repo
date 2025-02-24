/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:45:54 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/19 05:19:22 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cmds_array(t_node *final, t_mini *mini)
{
	t_node	*store;
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (get_num_command(final, mini) + 1));
	if (!args)
		clean_exit("malloc", mini);
	args[0] = NULL;
	if (mini->cmds)
	{
		ft_free_2d(&mini->cmds);
		mini->cmds = NULL;
	}
	mini->cmds = args;
	store = final;
	i = 0;
	while (store)
	{
		cmds_array_setter(&args, &i, store, mini);
		store = store->left;
	}
	args[i] = NULL;
	return (args);
}

void	expand_array(t_node *store, t_mini *mini, char ***args, int *i)
{
	char	**buf;
	int		k;

	if (store->token->value[0]
		&& *args[0] && ft_strncmp(*args[0], "export", 7) == 0)
	{
		(*args)[(*i)++] = ft_trim_quoted(store->token->value, 0, 0, mini);
		mini->temp_str = NULL;
	}
	else if (store->token->value[0])
	{
		buf = ft_split_space(store->token->value);
		if (!buf)
			clean_exit("malloc", mini);
		mini->temp_str = NULL;
		k = 0;
		while (buf[k])
			(*args)[(*i)++] = buf[k++];
		free(buf);
	}
	mini->temp_str = NULL;
	free (store->token->value);
}

char	*expand_home(t_mini *mini)
{
	char	*env;
	char	*name;

	name = ft_strdup("HOME");
	if (!name)
		clean_exit("malloc", mini);
	env = mygetenv(&name, mini);
	if (!env)
		return (free(name), NULL);
	return (free(name), env);
}

void	cmds_array_helper(char ***args, int *i, t_node *store, t_mini *mini)
{
	if (ft_strchr(store->token->value, '$'))
	{
		store->token->value = expand_env(store->token->value, mini, 0, 0);
		mini->temp_str = store->token->value;
		expand_array(store, mini, args, i);
	}
	else if (store->token->value[0] && ft_strcmp(store->token->value, "~") == 0)
	{
		(*args)[(*i)] = expand_home(mini);
		if (!(*args)[(*i)])
			return ;
		(*i)++;
	}
	else if (store->token->value[0])
		(*args)[(*i)++] = ft_trim_quoted(store->token->value, 0, 0, mini);
}

void	cmds_array_setter(char ***args, int *i, t_node *store, t_mini *mini)
{
	int		k;

	if (store->token->type == WILDCARD)
	{
		if (store->token->wild[0])
		{
			k = 0;
			while (store->token->wild[k])
			{
				(*args)[(*i)] = ft_strdup(store->token->wild[k++]);
				if (!(*args)[(*i)])
					clean_exit("malloc", mini);
				(*i)++;
			}
		}
		else
			(*args)[(*i)++] = ft_strdup(store->token->value);
	}
	else
		cmds_array_helper(args, i, store, mini);
}
