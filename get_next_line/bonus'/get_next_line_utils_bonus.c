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

t_list	*new_node(char *content)
{
	t_list	*node;

	node = (t_list *) malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = 0;
	return (node);
}

void	addback_node(t_list **lst, t_list *news)
{
	t_list	*temp;

	temp = *lst;
	if (!(*lst))
	{
		*lst = news;
		(*lst)->next = 0;
		return ;
	}
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = news;
	temp = news;
}

char   *save_string(t_list *list)
{
    int i;
    int j;
    char    *str;
	t_list *temp;

	temp = list;
    i = 0;
    j = 0;
	while (temp->next)
		temp = temp->next;
	while ((temp->content)[i] != '\n' && temp->content[i])
		i++;
	if ((temp->content)[i] == '\n')
		i++;
	if (!(temp->content)[i])
		return (NULL);
    str = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
    if (!str)
	{
		clear_node(&list);
		return (NULL);
	}
    while ((temp->content)[i])
    {
        str[j] = (temp->content)[i];
		j++;
		i++;
    }
    str[j] = '\0';
    return (str);
}

int string_length(t_list *list)
{
    t_list *temp;
    int i;
    int len;

    temp = list;
    len = 0;
    while (temp)
    {
        i = 0;
        while ((temp->content)[i])
        {
            if ((temp->content)[i] == '\n')
			{
				len++;
				return (len);
			}
            i++;
            len++;
        }
        temp = temp->next;
    }
    return(len);
}