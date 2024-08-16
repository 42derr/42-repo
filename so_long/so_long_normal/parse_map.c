#include "so_long.h"

void check_name (char *name)
{
    int len;
    int cmp;

    len = ft_strlen(name);
    cmp = ft_strncmp(".ber", name + (len - 4), 4);
    if (cmp != 0)
        map_err(0, 0, 0, "Map name should end with '.ber'\n");
}

void check_inside (t_map *map)
{
    int i;
    t_list *list;

    list = map->map_lst;
    while (list)
    {
        i = 0;
        while (((char *)list->content)[i])
        {
            if (ft_strchr("01EPC", ((char *)list->content)[i]) == 0)
                map_err(map, 0, 0, "Map only can contain 0, 1, E, C, P\n");
            i++;
        }
        list = list->next;
    }
}

void    read_map(t_map *map, char *map_name)
{
    char   *buffer;
    t_list *new;
    int mapfd;

    check_name(map_name);
    mapfd = open(map_name, O_RDONLY);
    if (mapfd == -1)
        map_err(0, 0, map_name, 0);
    buffer = get_next_line(mapfd);
    while (buffer != NULL)
    {
        if (buffer[ft_strlen(buffer) - 1] == '\n')
            buffer[ft_strlen(buffer) - 1] = '\0';
        new = ft_lstnew(buffer);
        if (!new)
            map_err(map, buffer, 0, "ft_lstnew\n"); //gnl lost
        ft_lstadd_back(&map->map_lst, new);
        buffer = get_next_line(mapfd);
    }
    map->height = ft_lstsize(map->map_lst);
    map->width = ft_strlen((char *)((map->map_lst)->content));
    if (map->height < 3 || map->width < 3)
         map_err(map, 0, 0, "Minimal valid height and width is 3\n");
    check_inside(map);
    check_map(map);
}