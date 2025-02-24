/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_temp_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:47:15 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:47:17 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_temp_env(char *str, t_mini *mini)
{
	char	*new;
	char	*old;
	t_list	*list;

	old = NULL;
	handle_temp_env_helper(str, mini, &new);
	if (ft_strchr(str, '$'))
		old = expand_env(str, mini, 0, 0);
	if (old)
	{
		mini->temp_str = old;
		new = ft_trim_quoted(old, 0, 0, mini);
		mini->temp_str = NULL;
		free(old);
	}
	else
		new = ft_trim_quoted(str, 0, 0, mini);
	list = ft_lstnew(new);
	if (!list)
		free_str_exit(&new, mini);
	ft_lstadd_back(&mini->temp_env, list);
	if (is_in_export(new, mini))
		append_export(new, mini, 0);
}

void	handle_old_temp(char **new, t_mini *mini, char **old, char *str)
{
	if (*old)
	{
		mini->temp_str = *old;
		*new = ft_trim_quoted(*old, 0, 0, mini);
		mini->temp_str = NULL;
		free(*old);
	}
	else
		*new = ft_trim_quoted(str, 0, 0, mini);
}

void	handle_temp_env_helper(char *str, t_mini *mini, char **new)
{
	t_list	*save;
	int		len;
	char	*old;

	len = ft_strchr(str, '=') - str;
	save = mini->temp_env;
	old = NULL;
	while (save)
	{
		if (ft_strncmp(str, (char *)save->content, len) == 0
			&& ((char *)save->content)[len] == '=')
		{
			free(save->content);
			if (ft_strchr(str, '$'))
				old = expand_env(str, mini, 0, 0);
			handle_old_temp(new, mini, &old, str);
			save->content = *new;
			if (is_in_export(*new, mini))
				append_export(*new, mini, 0);
			return ;
		}
		save = save->next;
	}
}

int	check_temp_env(char *new_str, t_mini *mini, char ***temp, int i)
{
	t_list	*temp_list;
	int		str_len;

	str_len = 0;
	if (!ft_strchr(new_str, '='))
	{
		temp_list = mini->temp_env;
		while (temp_list)
		{
			str_len = ft_strlen(new_str);
			if (ft_strncmp(temp_list->content, new_str, str_len) == 0
				&& ((char *)temp_list->content)[str_len] == '=')
			{
				(*temp)[i] = fix_syntax_new((char *)temp_list->content, mini);
				(*temp)[i + 1] = NULL;
				ft_free_2d(&mini->export_envp);
				mini->export_envp = *temp;
				sync_env((char *)temp_list->content, mini);
				return (1);
			}
			temp_list = temp_list->next;
		}
	}
	return (0);
}

char	*search_temp(char **str, t_mini *mini)
{
	t_list	*temp;
	char	*ret;

	temp = mini->temp_env;
	while (temp)
	{
		if (ft_strncmp((char *)temp->content, *str, ft_strlen(*str)) == 0)
		{
			if (((char *)temp->content)[ft_strlen(*str)] == '=')
			{
				ret = ft_strdup(temp->content + ft_strlen(*str) + 1);
				if (!ret)
				{
					free(*str);
					clean_exit("malloc", mini);
				}
				return (ret);
			}
		}
		temp = temp->next;
	}
	return (NULL);
}
