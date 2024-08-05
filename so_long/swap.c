#include "so_long.h"

int handle_ws(char *before, char *after, t_map *map)
{
    if (after[map->playerx] != '1')
    {
        if ((after[map->playerx] == 'C'))
        {
            map->collectible--;
            after[map->playerx] = 'P';
           before[map->playerx] = '0';
        }
        else if ((after[map->playerx] == 'E'))
        {
            if (map->collectible == 0)
                exit(0);
                return (printf("Collect all collectable !"), 1);
        }
        else
        {
            after[map->playerx] = 'P';
            before[map->playerx] = '0';
        }
        return (0);
    }        
    return (1);
}

int handle_ad(char *current, t_map *map, int j, int i)
{
    if (current[j] != '1')
    {
        if ((current[j] == 'C'))
        {
            map->collectible--;
            current[j] = 'P';
            current[i] = '0';
        }
        else if ((current[j] == 'E'))
        {
            if (map->collectible == 0)
                exit(0);
                return (printf("Collect all collectable !"), 1);
        }
        else
        {
            current[j] = 'P';
            current[i] = '0';
        }
        return (0);
    }        
    return (1);
}

void w_move(t_map *map)
{
    int i;
    char *temp_content;
    t_list *templist;

    i = 0;
    templist = map->map_lst;
    while (i < map->playery)
    {
        if (i == map->playery - 1)
            temp_content = ((char *)templist->content);
        templist = templist->next;
        i++;
    }
    i = handle_ws((char *)templist->content, temp_content, map);
    if (!i)
        map->playery--;
}

void s_move(t_map *map)
{
    int i;
    char *temp_content;
    t_list *templist;

    templist = map->map_lst;
    i = 0;
    while (i < map->playery + 1)
    {
        if (i == map->playery)
            temp_content = ((char *)templist->content);
        templist = templist->next;
        i++;
    }
    i = handle_ws(temp_content, (char *)templist->content, map);
    if (!i)
        map->playery++;     
}

void a_move(t_map *map)
{
    int i;
    char *temp_content;
    t_list *templist;

    templist = map->map_lst;
    i = 0;
    while (i < map->playery)
    {
        templist = templist->next;
        i++;
    }
    i = handle_ad((char *)templist->content, map, map->playerx - 1, map->playerx);
    if (!i)
        map->playerx--;     
}

void d_move(t_map *map)
{
    int i;
    char *temp_content;
    t_list *templist;

    templist = map->map_lst;
    i = 0;
    while (i < map->playery)
    {
        templist = templist->next;
        i++;
    }
    i = handle_ad((char *)templist->content, map, map->playerx + 1, map->playerx);
    if (!i)
        map->playerx++;     
}