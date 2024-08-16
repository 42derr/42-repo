#include "so_long.h"

int     key_hook(int keysym, t_var *data)
{
    if (keysym == XK_Escape)
        close_window(data);
    if (data->playery - 1 != 0 && data->amap[data->playery - 1][data->playerx] != '1' && keysym == XK_w)
    {
        hook_handler(data, data->playery - 1, data->playerx);
        data->playery--;
    }
    else if (data->playerx - 1 != 0 && data->amap[data->playery][data->playerx - 1] != '1'  && keysym == XK_a)
    {
        hook_handler(data, data->playery, data->playerx - 1);
        data->playerx--;
    }
    else if (data->playery + 1 != data->map->height - 1 && data->amap[data->playery + 1][data->playerx] != '1'  && keysym == XK_s)
    {
        hook_handler(data, data->playery + 1, data->playerx);
        data->playery++;
    }
    else if (data->playerx + 1 != data->map->width - 1 && data->amap[data->playery][data->playerx + 1] != '1' && keysym == XK_d)
    {
        hook_handler(data, data->playery, data->playerx + 1);
        data->playerx++;
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
    if (data->map->amap)
        free_array(data->map->amap);
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
    return (0);
}

int visual( t_map *map)
{
    t_var   data;

    data = (t_var){0};
    data.map = map;
    data.x = map->playerx * 32;
    data.y = map->playery * 32;
    data.playerx = map->playerx;
    data.playery = map->playery;
    data.amap = map->amap;
    data.mlx = mlx_init();
    if (!data.mlx)
        return (close_window(&data), 1);
    data.win = mlx_new_window(data.mlx, map->width * 32, map->height * 32, "so_long");
    if (!data.win)
        return (close_window(&data), 1);
    if (load_textures(&data))
        return (close_window(&data), 1);
    draw_textures (&data, map);
    mlx_put_image_to_window(data.mlx, data.win, data.textures[3], data.x, data.y);
    mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &close_window, &data);
    mlx_hook(data.win, KeyPress, KeyPressMask, &key_hook, &data);
    mlx_loop(data.mlx);
    return (0);
}