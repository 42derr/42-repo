#include "get_next_line.h"

char *string_malloc(t_list *list, char *str, int len)
{
    int     i;
    int     j;
    t_list *temp;

    temp = list;
    if(!temp)
        return (0);
    i = 0;
    while (len >= 0 && temp)
    {
        while (temp)
        {
            j = 0;
            while ((temp->content)[j] && len >= 0)
            {
                str[i] =(temp->content)[j];
                i++;
                j++;
                len--;
            }
            temp = temp->next;
        }
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

char *create_string_helper(int bytes_size, t_list **list)
{
    int len;
    char *str;

    if (bytes_size <= 0 && !*list)
        return (0);
    len = string_length(*list);
    str = (char *) malloc (sizeof(char) * (len + 2));
    if (!str)
         return (0);
    return (string_malloc(*list, str, len));
}

char *create_string(t_list **list, int fd)
{
    char    *buffer;
    int bytes_size;

    bytes_size = 0;
    while (!search_newline(*list))
    {
        buffer = (char *) malloc (sizeof(char) * (BUFFER_SIZE + 1));
        if (!buffer)
            return (0);
        bytes_size = read(fd, buffer, BUFFER_SIZE);
        if (bytes_size <= 0)
        {
            free(buffer);
            break ;
        }
        buffer[bytes_size] = '\0';
        addback_node (list, new_node(buffer));
    }
    return (create_string_helper(bytes_size, list));
}

char *get_next_line(int fd)
{
    static t_list *list = 0;
    char    *save_str;
    char    *final_string;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
    {
        clear_node(&list);
        return (0);
    }
    final_string = create_string(&list, fd);
    if (!final_string)
        return (0);
    save_str = save_string (list);
    clear_node(&list);
    if (save_str)
        addback_node(&list, new_node(save_str));        
    return (final_string);
}
