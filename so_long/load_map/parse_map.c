#include "../so_long.h"


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

int    check_map(t_map *map)
{
    int i;
    int j;
    t_list *maplist;
    

    maplist = map->map_lst;
    i = 0;
    while (i < map->height)
    {
        if (ft_strlen(maplist->content) != map->width)
            return (ft_putstr_fd("The map must be rectangular.\n", 2), 1);
        if (i == (map->height - 1) || i == 0)
        {
            j = 0;
            while (j < map->width)
            {
                if (((char *)maplist->content)[j] != '1')
                    return (ft_putstr_fd("The map must be surrounded by walls.\n", 2), 1);
                j++;
            }
        }
        else
            map_info(map, maplist, i);
        if (((char *)maplist->content)[0] != '1' || ((char *)maplist->content)[map->width - 1] != '1')
            return (ft_putstr_fd("The map must be surrounded by walls.\n", 2), 1);
        i++;
        maplist = maplist->next;
    }
    if (map->start != 1 || map->exit != 1 || map->collectible < 1)
        return (ft_putstr_fd("The map must contain 1 exit, at least 1 "
        "collectible, and 1 starting position.\n", 2), 1);
    if (validate_map(map) == false)
        return (ft_putstr_fd("There is no valid path.\n", 2), 1);
    create_enemy(map);
    return (0);
}

int create_enemy(t_map *map)
{
    int max_enemy;
    int cur_enemy;
    int y;
    int x;
    int i;

    max_enemy = (map->height / 2);
    srand(time(0));
    cur_enemy = 0;
    i = 0;
    while (cur_enemy < max_enemy && i < (map->height * map->width))
    {
        x = (rand() % (map->width - 1));
        y = (rand() % (map->height - 1));
        if (map->amap[y][x] == '0' && map->amap[y][x] != '1' &&  map->amap[y][x] !='C' &&  map->amap[y][x] != 'E' && !(y == map->playery && x == map->playerx))
        {
            map->amap[y][x] = 'X';
            if (validate_enemy(map))
            {
                cur_enemy++;
            }
            else
            {
                map->amap[y][x] = '0';
            }
        }
        i++;
    }
}

int clean_enemy(t_map *map)
{
    int y;
    int x;

    y = 0;
    while (map->amap[y])
    {
        x = 0;
        while (map->amap[y][x])
        {
            if (map->amap[y][x] == 'X')
                map->amap[y][x] = '0';
            x++;
        }
        y++;
    }
}

int    read_map(t_map *map, char *map_name)
{
    char   *buffer;
    t_list *new;
    int mapfd;

    mapfd = open(map_name, O_RDONLY);
    if (mapfd == -1)
        return (handle_error(map_name), 1);
    buffer = get_next_line(mapfd);
    while (buffer != NULL)
    {
        if (buffer[ft_strlen(buffer) - 1] == '\n')
            buffer[ft_strlen(buffer) - 1] = '\0';
        new = ft_lstnew(buffer);
        if (!new)
            return(ft_lstclear(&map->map_lst, &free), free(buffer), 1);// if this fail leaks in gnl
        ft_lstadd_back(&map->map_lst, new);
        buffer = get_next_line(mapfd);
    }
    map->height = ft_lstsize(map->map_lst);
    map->width = ft_strlen((char *)((map->map_lst)->content));
    if (check_map(map))
        return(ft_lstclear(&map->map_lst, &free), 1);
    return (0);
}