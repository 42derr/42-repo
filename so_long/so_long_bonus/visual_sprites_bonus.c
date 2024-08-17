#include "so_long_bonus.h"

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