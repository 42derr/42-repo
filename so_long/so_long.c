#include <stdio.h>
#include "so_long.h"

void print_content(void *content)
{
    // Assuming content is a string for this example
    printf("%s", (char *)content);
}

void    check_map(t_map *map)
{
    int i;
    int j;
    t_list *maplist;

    maplist = map->map_lst;
    i = map->height;
    while (i--)
    {
        if (ft_strlen(maplist->content) != map->width)
        {
            printf("len");
            return ;
        }
        if (i == (map->height - 1) || i == 0)
        {
            j = 0;
            while (j < map->width)
            {
                if (((char *)maplist->content)[j] != '1')
                {
                    printf("%s\n", ((char *)maplist->content));
                    printf("%d\n", i);
                    printf("wall");
                    return ;
                }
                j++;
            }
        }
        if (((char *)maplist->content)[0] != '1' || ((char *)maplist->content)[map->width - 1] != '1')
        {
            printf("len");
            return ;
        }
        maplist = maplist->next;
    }
}

void    read_map(t_map *map, int fd)
{
    char   *buffer;
    t_list *new;

    buffer = get_next_line(fd);
    while (buffer != NULL)
    {
        if (buffer[ft_strlen(buffer) - 1] == '\n')
            buffer[ft_strlen(buffer) - 1] = '\0';
        new = ft_lstnew(buffer);
        if (!buffer)
            return ;
        ft_lstadd_back(&map->map_lst, new);
        buffer = get_next_line(fd);
    }
    map->height = ft_lstsize(map->map_lst);
    map->width = ft_strlen((char *)((map->map_lst)->content));
    // ft_lstiter(list, &print_content);
    // printf("\n");
    check_map(map);
}

int main(int agrc, char **argv)
{
    int mapfd;
    char    *map_name;
    t_map map;

    map = (t_map) {0};
    map_name = argv[1];
    mapfd = open(map_name, O_RDONLY);
    if (!mapfd)
        return (0);
    read_map(&map, mapfd);
}