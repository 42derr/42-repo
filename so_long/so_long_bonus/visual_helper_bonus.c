#include "so_long_bonus.h"

void    draw_image(t_var *data, void *img, int x, int y)
{
    mlx_put_image_to_window(data->mlx, data->win, img, x, y);
}

void render(t_var *game) 
{
    draw_textures(game, game->map);
    display_move(game);
    mlx_put_image_to_window(game->mlx, game->win, game->sprites[game->direction][game->current_sprite], game->x, game->y);
}

void    draw_textures_helper(t_var *data, t_map *map, int i, int y)
{
    int j;
    int x;

    j = 0;
    x = 0;
    while (j < map->width)
    {
        if (data->amap[i][j] == '1')
            draw_image(data, data->textures[0], x, y);
        else if (data->amap[i][j] == '0' || map->amap[i][j] == 'P')
            draw_image(data, data->textures[2], x, y);
        else if (data->amap[i][j] == 'E')
            draw_image(data, data->textures[1], x, y);
        else if (data->amap[i][j] == 'C')
            draw_image(data, data->textures[4], x, y);
        else if (data->amap[i][j] == 'X')
            draw_image(data, data->textures[5], x, y);
        j++;
        x += 32;
    }
}

void    draw_textures(t_var *data, t_map *map)
{
    int y;
    int i;

    y = 0;
    i = 0;
    while (data->amap[i])
    {
        draw_textures_helper(data, map, i, y);
        i++;
        y += 32;
    }
}

void     hook_handler(t_var *data, int y, int x)
{
    data->move++;
    if (data->amap[y][x] == 'E')
    {
        if (data->map->collectible != 0)
            ft_putstr_fd("Collect all collectable !\n", 1);
        close_window(data);
    }
    if (data->amap[y][x] == 'C')
    {
        data->map->collectible--;
        data->amap[y][x] = '0';
    }
    if (data->amap[y][x] == 'X')
    {
        ft_putstr_fd("YOU LOSE !\n", 1);
        close_window(data);
    }
}
