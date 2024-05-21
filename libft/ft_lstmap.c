/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:42:49 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/20 17:07:56 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>
/*
void	ft_del(void *content)
{
	free(content);
}

void	*ft_tp(void *content)
{
	int	i;
	char	*str;
	char	*cont;

	cont = (char *) content;
	i = 0;
	while (cont[i])
		i++;
	str = (char *) malloc (sizeof(char) * (i + 1));
	i = 0;
	while (cont[i])
	{
		if (cont[i] >= 'a' && cont[i] <= 'z')
			str[i] = cont[i] - 32;
		else
			str[i] = cont[i];
		i++;
	}
	str[i] = '\0';
	return ((void *)str);
}
*/

static t_list	*fl(t_list *l, t_list *n, void *(*f)(void *), void (*d)(void *))
{
	t_list	*nextlist;

	nextlist = (t_list *) malloc (sizeof(t_list));
	if (!nextlist)
		return (0);
	n->content = f(l->content);
	n->next = nextlist;
	if (l->next)
		n = n->next;
	else
	{
		n->next = 0;
		d(nextlist);
	}
	return (n);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*firstlist;

	if (!lst)
		return (0);
	firstlist = (t_list *) malloc(sizeof (t_list));
	if (!firstlist)
		return (0);
	newlist = (t_list *) malloc (sizeof(t_list));
	if (!newlist)
		return (0);
	firstlist->content = f(lst->content);
	firstlist->next = newlist;
	if (!(lst->next))
	{
		firstlist->next = 0;
		del(newlist);
	}
	lst = lst->next;
	while (lst)
	{
		newlist = fl(lst, newlist, f, del);
		lst = lst->next;
	}
	return (firstlist);
}
/*
#include <stdio.h>

int	main(void)
{
	t_list test3 = { .content = "hello3", .next = 0};
	t_list test2 = { .content = "hello2", .next = &test3};
	t_list test1 = { .content = "hello1", .next = &test2};
	t_list *mapped;

	mapped = ft_lstmap (&test1, &ft_tp, &ft_del);


	while (mapped)
	{
		printf("%s\n", (char *)mapped->content);
		mapped = mapped->next;
	}
}
*/
