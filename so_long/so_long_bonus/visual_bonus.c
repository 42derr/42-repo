#include "so_long_bonus.h"

void update_helper(t_var *game)
{
    if (game->is_moving) 
    {
        game->current_sprite = (game->current_sprite + 1) % 4;
        if (game->direction == RIGHT)
            game->x += SPRITE_SIZE / 4;
        else if (game->direction == LEFT)
            game->x -= SPRITE_SIZE / 4;
        else if (game->direction == FRONT)
            game->y -= SPRITE_SIZE / 4;
        else if (game->direction == BACK)
            game->y += SPRITE_SIZE / 4;
        render(game);
        usleep(ANIMATION_DELAY);
        if (game->current_sprite == 0)
            game->is_moving = 0;
    }
}

int update(t_var *game) 
{
    time_t current_time;

    time(&current_time);
    if (difftime(current_time, game->last_update) >= 10.0) 
    {
        clean_enemy(game->map);
        create_enemy(game->map);
        render(game);
        game->last_update = current_time;
    }
    update_helper(game);
    return (0);
}

void    key_handler(t_var *data, int i)
{
    if (i == 0)
    {
        data->is_moving = 1;
        data->direction = FRONT;
        data->playery--;
    }
    else if (i == 1)
    {
        data->is_moving = 1;
        data->direction = LEFT;
        data->playerx--;
    }
    else if (i == 2)
    {
        data->is_moving = 1;
        data->direction = BACK;
        data->playery++;
    }
    else if (i == 3)
    {
        data->is_moving = 1;
        data->direction = RIGHT;
        data->playerx++;
    }
}

int     key_hook(int keysym, t_var *data)
{
    if (keysym == XK_Escape)
        close_window(data);
    if (data->playery - 1 != 0 && data->amap[data->playery - 1][data->playerx] != '1' && keysym == XK_w && !data->is_moving)
    {
        hook_handler(data, data->playery - 1, data->playerx);
        key_handler(data, 0);
    }
    else if (data->playerx - 1 != 0 && data->amap[data->playery][data->playerx - 1] != '1'  && keysym == XK_a && !data->is_moving)
    {
        hook_handler(data, data->playery, data->playerx - 1);
        key_handler(data, 1);
    }
    else if (data->playery + 1 != data->map->height - 1 && data->amap[data->playery + 1][data->playerx] != '1'  && keysym == XK_s && !data->is_moving)
    {
        hook_handler(data, data->playery + 1, data->playerx);
        key_handler(data, 2);
    }
    else if (data->playerx + 1 != data->map->width - 1 && data->amap[data->playery][data->playerx + 1] != '1' && keysym == XK_d && !data->is_moving)
    {
        hook_handler(data, data->playery, data->playerx + 1);
        data->is_moving = 1;
        data->direction = RIGHT;
        data->playerx++;
    }
    render(data);
    return (0);
}

int visual( t_map *map)
{
    t_var   data;

    data = (t_var){0};
    data.map = map;
    data.mlx = mlx_init();
    data.direction = BACK;
    data.x = map->playerx * 32;
    data.y = map->playery * 32;
    data.playerx = map->playerx;
    data.playery = map->playery;
    data.amap = map->amap;
    if (!data.mlx)
        return (close_window(&data), 1);
    data.win = mlx_new_window(data.mlx, map->width * 32, (map->height + 1) * 32, "so_long");
    if (!data.win)
        return (close_window(&data), 1);
    if (load_textures(&data))
        return (close_window(&data), 1);
    render(&data);
    mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &close_window, &data);
    mlx_hook(data.win, KeyPress, KeyPressMask, &key_hook, &data);
    mlx_loop_hook(data.mlx, update, &data);
    mlx_loop(data.mlx);
    return 0;
}
