#include <stdio.h>
#include "so_long.h"

void print_content(void *content)
{
    // Assuming content is a string for this example
    printf("%s\n", (char *)content);
}

void    read_map(t_list *map, int fd)
{
    char   *buffer;
    t_list *new;
    t_list *list;

    list = NULL;
    buffer = get_next_line(fd);
    print_content(buffer);
    while (buffer != NULL)
    {
            new = ft_lstnew(buffer);
            if (!buffer)
                return ;
            ft_lstadd_back(&list, new);
            buffer = get_next_line(fd);
    }
    ft_lstiter(list, &print_content);
}

int main(int agrc, char **argv)
{
    int mapfd;
    char    *map_name;
    t_list map;

    map = (t_list){0};
    map_name = argv[1];
    mapfd = open(map_name, O_RDONLY);
    if (!mapfd)
        return (0);
    read_map(&map, mapfd);
}