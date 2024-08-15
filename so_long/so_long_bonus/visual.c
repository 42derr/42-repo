#include "so_long.h"

void    draw_image(t_var *data, void *img, int x, int y)
{
    mlx_put_image_to_window(data->mlx, data->win, img, x, y);
}

void render(t_var *game) 
{
    draw_textures(game, game->map);
    mlx_put_image_to_window(game->mlx, game->win, game->sprites[game->direction][game->current_sprite], game->x, game->y);
}

int update(t_var *game) {

    time_t current_time;
    time(&current_time);

    if (difftime(current_time, game->last_update) >= 10.0) {
        clean_enemy(game->map);
        create_enemy(game->map);
        render(game);
        game->last_update = current_time;
    }
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
    return 0;
}


void    draw_textures(t_var *data, t_map *map)
{
    int x;
    int y;
    int j;
    int i;

    y = 0;
    i = 0;
    while (data->amap[i])
    {
        j = 0;
        x = 0;
        while (j < map->width)
        {
            if (data->amap[i][j] == '1')
                draw_image(data, data->textures[0], x, y);
            else if (data->amap[i][j] == '0')
                draw_image(data, data->textures[2], x, y);
            else if (data->amap[i][j] == 'P')
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
        i++;
        y += 32;
    }
    display_move(data);
}

int     key_hook(int keysym, t_var *data)
{
    if (keysym == XK_Escape)
        close_window(data);
    if (data->playery - 1 != 0 && data->amap[data->playery - 1][data->playerx] != '1' && keysym == XK_w && !data->is_moving)
    {
        if (data->amap[data->playery - 1][data->playerx] == 'E')
        {
            if (data->map->collectible != 0)
                return (printf("Collect all collectable !\n"), 0);
            close_window(data);
        }
        if (data->amap[data->playery - 1][data->playerx] == 'X')
        {
            printf("YOU LOSE !\n");
            close_window(data);
        }
        if (data->amap[data->playery - 1][data->playerx] == 'C')
        {
            data->map->collectible--;
            data->amap[data->playery - 1][data->playerx] = '0';
        }
        data->is_moving = 1;
        data->direction = FRONT;
        data->playery--;
        data->move++;
    }
    else if (data->playerx - 1 != 0 && data->amap[data->playery][data->playerx - 1] != '1'  && keysym == XK_a && !data->is_moving)
    {
        if ( data->amap[data->playery][data->playerx - 1] == 'E')
        {
            if (data->map->collectible != 0)
                return (printf("Collect all collectable !\n"), 0);
            close_window(data);
        }
        if (data->amap[data->playery][data->playerx - 1] == 'X')
        {
            printf("YOU LOSE !\n");
            close_window(data);
        }
        if (data->amap[data->playery][data->playerx - 1] == 'C')
        {
            data->map->collectible--;
            data->amap[data->playery][data->playerx - 1] = '0';
        }
        data->is_moving = 1;
        data->direction = LEFT;
        data->playerx--;
        data->move++;
    }
    else if (data->playery + 1 != data->map->height - 1 && data->amap[data->playery + 1][data->playerx] != '1'  && keysym == XK_s && !data->is_moving)
    {
        if (data->amap[data->playery + 1][data->playerx]  == 'E')
        {
            if (data->map->collectible != 0)
                return (printf("Collect all collectable !\n"), 0);
            close_window(data);
        }
        if (data->amap[data->playery + 1][data->playerx] == 'X')
        {
            printf("YOU LOSE !\n");
            close_window(data);
        }
        if (data->amap[data->playery + 1][data->playerx] == 'C')
        {
            data->map->collectible--;
            data->amap[data->playery + 1][data->playerx] = '0';
        }
        data->is_moving = 1;
        data->direction = BACK;
        data->playery++;
        data->move++;
    }
    else if (data->playerx + 1 != data->map->width - 1 && data->amap[data->playery][data->playerx + 1] != '1' && keysym == XK_d && !data->is_moving)
    {
        if (data->amap[data->playery][data->playerx + 1] == 'E')
        {
            if (data->map->collectible != 0)
                return (printf("Collect all collectable !\n"), 0);
            close_window(data);
        }
        if (data->amap[data->playery][data->playerx + 1] == 'X')
        {
            printf("YOU LOSE !\n");
            close_window(data);
        }
        if (data->amap[data->playery][data->playerx + 1] == 'C')
        {
            data->map->collectible--;
            data->amap[data->playery][data->playerx + 1] = '0';
        }
        data->is_moving = 1;
        data->direction = RIGHT;
        data->playerx++;
        data->move++;
    }
    render(data);
    return (0);
}

int close_window(t_var *data)
{
    if (data->mlx && data->textures[0])
        mlx_destroy_image(data->mlx, data->textures[0]);
    if (data->mlx && data->textures[1])
        mlx_destroy_image(data->mlx, data->textures[1]);
    if (data->mlx && data->textures[2])
        mlx_destroy_image(data->mlx, data->textures[2]);
    if (data->mlx && data->textures[3])
        mlx_destroy_image(data->mlx, data->textures[3]);
    if (data->mlx && data->textures[4])
        mlx_destroy_image(data->mlx, data->textures[4]);
    if (data->mlx && data->win)
        mlx_destroy_window(data->mlx, data->win);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    if (data->string_move)
        free(data->string_move);
    if ((data->map)->map_lst)
        ft_lstclear(&((data->map)->map_lst), &free);
    exit(1);
    return (0);
}

int load_textures(t_var *data)
{
    data->textures[0] = mlx_xpm_file_to_image(data->mlx, "textures/hedge.xpm", &data->texture_length, &data->texture_length);
    if (!data->textures[0])
        return (ft_putstr_fd("Failed to load textures/headge.xpm", 2), 1);
    data->textures[1] = mlx_xpm_file_to_image(data->mlx, "textures/portal.xpm", &data->texture_length, &data->texture_length);
    if (!data->textures[1])
        return (ft_putstr_fd("Failed to load textures/portal.xpm", 2), 1);
    data->textures[2] = mlx_xpm_file_to_image(data->mlx, "textures/background.xpm", &data->texture_length, &data->texture_length);
    if (!data->textures[2])
        return (ft_putstr_fd("Failed to load textures/background.xpm", 2), 1);
    data->textures[3] = mlx_xpm_file_to_image(data->mlx, "textures/mainchar.xpm", &data->texture_length, &data->texture_length);
    if (!data->textures[3])
        return (ft_putstr_fd("Failed to load textures/mainchar.xpm", 2), 1);
    data->textures[4] = mlx_xpm_file_to_image(data->mlx, "textures/rose.xpm", &data->texture_length, &data->texture_length);
    if (!data->textures[4])
        return (ft_putstr_fd("Failed to load textures/rose.xpm", 2), 1);
    data->textures[5] = mlx_xpm_file_to_image(data->mlx, "textures/ghost.xpm", &data->texture_length, &data->texture_length);
    if (!data->textures[5])
        return (ft_putstr_fd("Failed to load textures/ghost.xpm", 2), 1);
    load_sprites(data);
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
