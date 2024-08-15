#include "so_long.h"

void    draw_image(t_var *data, void *img, int x, int y)
{
    mlx_put_image_to_window(data->mlx, data->win, img, x, y);
}

void    draw_textures(t_var *data, t_map *map)
{
    int x;
    int y;
    int j;
    t_list *maplist;

    maplist = map->map_lst;
    y = 0;
    while (maplist)
    {
        j = 0;
        x = 0;
        while (j < map->width)
        {
            if (((char *)maplist->content)[j] == '1')
                draw_image(data, data->textures[0], x, y);
            else if (((char *)maplist->content)[j] == '0')
                draw_image(data, data->textures[2], x, y);
            else if (((char *)maplist->content)[j] == 'P')
                draw_image(data, data->textures[3], x, y);
            else if (((char *)maplist->content)[j] == 'E')
                draw_image(data, data->textures[1], x, y);
            else if (((char *)maplist->content)[j] == 'C')
                draw_image(data, data->textures[4], x, y);
            j++;
            x += 32;
        }
        y += 32;
        maplist = maplist->next;
    }
    display_move(data);
}

int     key_hook(int keysym, t_var *data)
{
    if (keysym == XK_Escape)
        close_window(data);
    if (keysym == XK_w)
        w_move((data->map), data);
    else if (keysym == XK_a)
        a_move((data->map), data);
    else if (keysym == XK_s)
        s_move((data->map), data);
    else if (keysym == XK_d && !data->is_moving)
        d_move((data->map), data);
    draw_textures(data, data->map);
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
    return (0);
}

int visual( t_map *map)
{
    t_var   data;

    data = (t_var){0};
    data.map = map;
    data.mlx = mlx_init();
    if (!data.mlx)
        return (close_window(&data), 1);
    data.win = mlx_new_window(data.mlx, map->width * 32, (map->height + 1) * 32, "so_long");
    if (!data.win)
        return (close_window(&data), 1);
    if (load_textures(&data))
        return (close_window(&data), 1);
    draw_textures(&data, map);
    mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &close_window, &data);
    mlx_key_hook(data.win, key_hook, &data);
    mlx_loop(data.mlx);
    return 0;
}
