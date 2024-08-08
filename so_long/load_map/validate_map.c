#include "../so_long.h"


bool    run_map(int x, int y, t_map *map)
{
    if (x < 0 || x >= map->width || y < 0 || y >= map->height || map->visited[y][x] == true || map->amap[y][x] == '1')
        return (false);
    map->visited[y][x] = true;
    if (map->amap[y][x] == 'C')
        map->valid_col--;
    else if (map->amap[y][x] == 'E')
        map->exit--;
    if (map->valid_col == 0 && map->exit == 0)
        return (true);
    return (run_map(x + 1, y, map) ||
           run_map(x - 1, y, map) ||
           run_map(x, y + 1, map) ||
           run_map(x, y - 1, map));
}

bool    validate_map(t_map *map)
{
    bool path_found;
    bool path_valid;

    map->valid_col = map->collectible;
    generate_arraymap(map);
    if (!map->amap)
        return (false);
    map->visited = generate_visited(map);
    if (!map->visited)
        return (free_array(map->amap), false);
    path_found = run_map(map->playerx, map->playery, map);
    path_valid = path_found && map->valid_col == 0 && map->exit == 0;
    free_bool(map->visited, map->height);
    free_array(map->amap);
    return path_valid;
}

bool    **generate_visited(t_map *map)
{
    bool **visited;
    bool *buffer;
    int j;
    int i;

    j = 0;
    i = 0;
    visited = (bool **) malloc (sizeof(bool *) * map->height);
    if (!visited)
        return (NULL);
    while (j < map->height)
    {
        buffer = (bool *) malloc (sizeof(bool) * map->width);
        if (!buffer)
            return (free_bool(visited, j), NULL);
        i = 0;
        while (i < map->width)
        {
            buffer[i] = false;
            i++;
        }
        visited[j] = buffer;
        j++;
    }
    return visited;
}

void    generate_arraymap(t_map *map)
{
    t_list *maplist;
    char *buffer;
    char *new;
    char **amap;

    maplist = map->map_lst;
    buffer = ft_strdup("");
    if (!buffer)
        return ;
    while(maplist)
    {
        new = ft_strjoin(buffer, ";");
        free(buffer);
        if (!new)
            return ;
        buffer = ft_strjoin(new, (char *) maplist->content);
        free(new);
        if (!buffer)
            return ;
        maplist = maplist->next;
    }
    map->amap = ft_split(buffer, ';');
    free(buffer);
}