#include "so_long.h"

int load_sprites_back(t_var *data)
{
    data->sprites[0][0] = mlx_xpm_file_to_image(data->mlx, "textures/char/back/back1.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][0])
        return (ft_putstr_fd("Failed to load textures/char/back/back1.xpm", 2), 1);
    data->sprites[0][1] = mlx_xpm_file_to_image(data->mlx, "textures/char/back/back2.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][1])
        return (ft_putstr_fd("Failed to load textures/char/back/back2.xpm", 2), 1);
    data->sprites[0][2] = mlx_xpm_file_to_image(data->mlx, "textures/char/back/back3.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][2])
        return (ft_putstr_fd("Failed to load textures/char/back/back3.xpm", 2), 1);
    data->sprites[0][3] = mlx_xpm_file_to_image(data->mlx, "textures/char/back/back4.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][3])
        return (ft_putstr_fd("Failed to load textures/char/back/back4.xpm", 2), 1);
    return (0);
}

int load_sprites_right(t_var *data)
{
    data->sprites[0][0] = mlx_xpm_file_to_image(data->mlx, "textures/char/right/right1.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][0])
        return (ft_putstr_fd("Failed to load textures/char/right/right1.xpm", 2), 1);
    data->sprites[0][1] = mlx_xpm_file_to_image(data->mlx, "textures/char/right/right2.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][1])
        return (ft_putstr_fd("Failed to load textures/char/right/right2.xpm", 2), 1);
    data->sprites[0][2] = mlx_xpm_file_to_image(data->mlx, "textures/char/right/right3.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][2])
        return (ft_putstr_fd("Failed to load textures/char/right/right3.xpm", 2), 1);
    data->sprites[0][3] = mlx_xpm_file_to_image(data->mlx, "textures/char/right/right4.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][3])
        return (ft_putstr_fd("Failed to load textures/char/right/right4.xpm", 2), 1);
    return (0);
}

int load_sprites_left(t_var *data)
{
    data->sprites[0][0] = mlx_xpm_file_to_image(data->mlx, "textures/char/left/left1.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][0])
        return (ft_putstr_fd("Failed to load textures/char/left/left1.xpm", 2), 1);
    data->sprites[0][1] = mlx_xpm_file_to_image(data->mlx, "textures/char/left/left2.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][1])
        return (ft_putstr_fd("Failed to load textures/char/left/left2.xpm", 2), 1);
    data->sprites[0][2] = mlx_xpm_file_to_image(data->mlx, "textures/char/left/left3.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][2])
        return (ft_putstr_fd("Failed to load textures/char/left/left3.xpm", 2), 1);
    data->sprites[0][3] = mlx_xpm_file_to_image(data->mlx, "textures/char/left/left4.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][3])
        return (ft_putstr_fd("Failed to load textures/char/left/left4.xpm", 2), 1);
    return (0);
}

int load_sprites_front(t_var *data)
{
    data->sprites[0][0] = mlx_xpm_file_to_image(data->mlx, "textures/char/front/front1.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][0])
        return (ft_putstr_fd("Failed to load textures/char/front/front1.xpm", 2), 1);
    data->sprites[0][1] = mlx_xpm_file_to_image(data->mlx, "textures/char/front/front2.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][1])
        return (ft_putstr_fd("Failed to load textures/char/front/front2.xpm", 2), 1);
    data->sprites[0][2] = mlx_xpm_file_to_image(data->mlx, "textures/char/front/front3.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][2])
        return (ft_putstr_fd("Failed to load textures/char/front/front3.xpm", 2), 1);
    data->sprites[0][3] = mlx_xpm_file_to_image(data->mlx, "textures/char/front/front4.xpm", &data->texture_length, &data->texture_length);
    if (!data->sprites[0][3])
        return (ft_putstr_fd("Failed to load textures/char/front/front4.xpm", 2), 1);
    return (0);
}

int load_sprites(t_var *data)
{
    if (load_sprites_front(data))
        return (1);
    if (load_sprites_back(data))
        return (1);
    if (load_sprites_left(data))
        return (1);
    if (load_sprites_right(data))
        return (1);
    return (0);
}
