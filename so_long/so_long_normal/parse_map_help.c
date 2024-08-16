#include "so_long.h"

void    map_info(t_map *map, t_list *maplist, int i)
{
    int j;

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

void check_map_helper(t_map * map, t_list *maplist, int i)
{
    int j;

    j = 0;
    if (ft_strlen(maplist->content) != map->width)
        map_err(map, 0, 0, "The map must be rectangular.\n");
    if (i == (map->height - 1) || i == 0)
    {
        j = 0;
        while (j < map->width)
        {
            if (((char *)maplist->content)[j] != '1')
                map_err(map, 0, 0, "The map must be surrounded by walls.\n");
            j++;
        }
    }
    else
        map_info(map, maplist, i);
    if (((char *)maplist->content)[0] != '1' || ((char *)maplist->content)[map->width - 1] != '1')
        map_err(map, 0, 0, "The map must be surrounded by walls.\n");
}

void    check_map(t_map *map)
{
    int i;
    int j;
    t_list *maplist;
    

    maplist = map->map_lst;
    i = 0;
    while (i < map->height)
    {
        check_map_helper(map, maplist, i);
        i++;
        maplist = maplist->next;
    }
    if (map->start != 1 || map->exit != 1 || map->collectible < 1)
        map_err(map, 0, 0, "The map must contain 1 exit, at least 1 "
        "collectible, and 1 starting position.\n");
    if (validate_map(map) == false)
        map_err(map, 0, 0, "There is no valid path.\n");
}