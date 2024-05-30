#include "get_next_line.h"
#include <stdio.h>

char *string_malloc(t_list *list, char *str, int len)
{
    int     i;
    int     j;
    t_list *temp;

    temp = list;
    i = 0;
    while (len > 0 && temp)
    {
        j = 0;
        while ((temp->content)[j] && len > 0)
        {
            str[i++] =(temp->content)[j++];
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
    t_list *temp;

    temp = list;
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
    return(0);
}

char *create_string(t_list **list, int fd)
{
    char    *str;
    char    *buffer;
    int len;
    int bytes_size;
    t_list *new_list;

    bytes_size = 0;
    while (!search_newline(*list))
    {
        buffer = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
        if (!buffer)
            return (NULL);
        bytes_size = read(fd, buffer, BUFFER_SIZE);
        if (bytes_size <= 0)
        {
            free(buffer);
            break ;
        }
        buffer[bytes_size] = '\0';
        new_list = new_node(buffer);
        if (!new_list)
        {
            free(buffer);
            return (NULL);
        }
        addback_node (list, new_list);
    }
    if ((bytes_size <= 0 && !(*list)) || bytes_size == -1)
        return (NULL);
    len = string_length(*list);
    str = (char *) malloc (sizeof(char) * (len + 1));
    if (!str)
         return (NULL);
    return (string_malloc(*list, str, len));
}

char *get_next_line(int fd)
{
    static t_list *list[1024] = {0};
    char    *save_str;
    char    *final_string;

    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
    {
        clear_node(&list[fd]);
        return (NULL);
    }
    final_string = create_string(&list[fd], fd);
    if (!final_string)
    {
        clear_node(&list[fd]);
        return (NULL);
    }
    save_str = save_string (list[fd]);
    if (!save_str && !list[fd])
        return (NULL);
    clear_node(&list[fd]);
    if (save_str)
        addback_node(&list[fd], new_node(save_str));     
    return (final_string);
}
