#include <stdio.h>
#include "so_long.h"

void    check_map(t_map *map)
{
    int i;
    int j;
    t_list *maplist;
    

    maplist = map->map_lst;
    i = 0;
    while (i < map->height)
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
                    printf("%d\n", i);
                    printf("%s\n", ((char *)maplist->content));
                    printf("wall");
                    return ;
                }
                j++;
            }
        }
        else
        {
            j = 0;
            while (j < map->width)
            {
                if (((char *)maplist->content)[j] == 'E')
                    map->exit++;
                if (((char *)maplist->content)[j] == 'C')
                    map->collectible++;
                if (((char *)maplist->content)[j] == 'P')
                {
                    map->start++;
                    map->playerx = j;
                    map->playery = i;
                }
                j++;
            }
        }
        if (((char *)maplist->content)[0] != '1' || ((char *)maplist->content)[map->width - 1] != '1')
        {
            printf("len");
            return ;
        }
        i++;
        maplist = maplist->next;
    }
    if (map->start != 1 || map->exit != 1 || map->collectible < 1)
    {
        printf("len");
        return ;
    }
    //check if it valid
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
    visual((map.width * 32),(map.height * 32), &map);
}