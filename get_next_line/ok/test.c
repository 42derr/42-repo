#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_FD 1024 // Define a reasonable maximum number of file descriptors

char *string_malloc(t_list *list, char *str, int len);
int search_newline(t_list *list);
char *create_string(t_list **list, int fd);
void clear_node(t_list **lst);
t_list *new_node(char *content);
void addback_node(t_list **lst, t_list *news);
char *save_string(t_list *list);
int string_length(t_list *list);

char *string_malloc(t_list *list, char *str, int len)
{
    int i = 0, j;
    t_list *temp = list;

    while (len > 0 && temp)
    {
        j = 0;
        while ((temp->content)[j] && len > 0)
        {
            str[i++] = (temp->content)[j++];
            len--;
        }
        temp = temp->next;
    }
    str[i] = '\0';
    return (str);
}

int search_newline(t_list *list)
{
    int i;
    t_list *temp = list;

    while (temp)
    {
        i = 0;
        while ((temp->content)[i])
        {
            if ((temp->content)[i] == '\n')
                return (1);
            i++;
        }
        temp = temp->next;
    }
    return (0);
}

char *create_string(t_list **list, int fd)
{
    char *str, *buffer;
    int len, bytes_size;
    t_list *new_list;

    bytes_size = 0;
    while (!search_newline(*list))
    {
        buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if (!buffer)
            return (NULL);
        bytes_size = read(fd, buffer, BUFFER_SIZE);
        printf("Read %d bytes\n", bytes_size); // Debug statement
        if (bytes_size <= 0)
        {
            free(buffer);
            break;
        }
        buffer[bytes_size] = '\0';
        new_list = new_node(buffer);
        if (!new_list)
        {
            free(buffer);
            return (NULL);
        }
        addback_node(list, new_list);
    }
    if (bytes_size <= 0 && !(*list))
        return (NULL);
    len = string_length(*list);
    printf("String length calculated: %d\n", len); // Debug statement
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    return (string_malloc(*list, str, len));
}


char *get_next_line(int fd)
{
    static t_list *list[MAX_FD] = {0};
    char *save_str;
    char *final_string;

    if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD || read(fd, NULL, 0) < 0)
    {
        if (fd >= 0 && fd < MAX_FD)
            clear_node(&list[fd]);
        return (NULL);
    }
    final_string = create_string(&list[fd], fd);
    if (!final_string)
    {
        clear_node(&list[fd]);
        return (NULL);
    }
    save_str = save_string(list[fd]);
    clear_node(&list[fd]);
    if (save_str)
        addback_node(&list[fd], new_node(save_str));
    return (final_string);
}


void clear_node(t_list **lst)
{
    t_list *next_node;

    while (*lst)
    {
        next_node = (*lst)->next;
        free((*lst)->content);
        free(*lst);
        *lst = next_node;
    }
    *lst = 0;
}

t_list *new_node(char *content)
{
    t_list *node = (t_list *)malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->content = content;
    node->next = 0;
    return (node);
}

void addback_node(t_list **lst, t_list *news)
{
    t_list *temp;

    if (!(*lst))
    {
        *lst = news;
        (*lst)->next = 0;
        return;
    }
    temp = *lst;
    while (temp->next)
    {
        temp = temp->next;
    }
    temp->next = news;
}

char *save_string(t_list *list)
{
    int i = 0, j = 0;
    char *str;
    t_list *temp = list;

    while (temp->next)
        temp = temp->next;
    while ((temp->content)[i] != '\n' && (temp->content)[i])
        i++;
    if ((temp->content)[i] == '\n')
        i++;
    if (!(temp->content)[i])
    {
        printf("No content to save after newline.\n"); // Debug statement
        return (NULL);
    }
    str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!str)
    {
        clear_node(&list);
        return (NULL);
    }
    while ((temp->content)[i])
    {
        str[j++] = (temp->content)[i++];
    }
    str[j] = '\0';
    printf("Saved string: %s\n", str); // Debug statement
    return (str);
}


int string_length(t_list *list)
{
    t_list *temp = list;
    int i, len = 0;

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
    return (len);
}
