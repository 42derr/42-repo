/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:57:24 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/29 18:49:47 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_node(t_list **lst)
{
	t_list	*next_node;

	while (*lst)
	{
		next_node = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = next_node;
	}
	*lst = 0;
}

int	addback_new_node(t_list **lst, char **content)
{
	t_list	*temp;
	t_list	*news;

	news = (t_list *) malloc(sizeof(t_list));
	if (!news)
	{
		free(*content);
		return (0);
	}
	news->content = *content;
	news->next = 0;
	temp = *lst;
	if (!(*lst))
	{
		*lst = news;
		(*lst)->next = 0;
		return (1);
	}
	while (temp->next)
		temp = temp->next;
	temp->next = news;
	temp = news;
	return (1);
}

int	save_string_helper(int i, int j, char *content, t_list **list)
{
	char	*str;

	str = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (0);
	while (content[i])
		str[j++] = content[i++];
	str[j] = '\0';
	clear_node(list);
	if (addback_new_node (list, &str) == 0)
		return (0);
	return (1);
}

int	save_string(t_list **list)
{
	int		i;
	int		j;
	t_list	*temp;

	temp = *list;
	i = 0;
	j = 0;
	while (temp->next)
		temp = temp->next;
	while (((char *)(temp->content))[i] != '\n' && ((char *)(temp->content))[i])
		i++;
	if (((char *)(temp->content))[i] == '\n')
		i++;
	if (!((char *)(temp->content))[i])
	{
		clear_node(list);
		return (1);
	}
	return (save_string_helper(i, j, (temp->content), list));
}

int	string_length(t_list *list)
{
	t_list	*temp;
	int		i;
	int		len;

	temp = list;
	len = 0;
	while (temp)
	{
		i = 0;
		while (((char *)(temp->content))[i])
		{
			if (((char *)(temp->content))[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		temp = temp->next;
	}
	return (len);
}
