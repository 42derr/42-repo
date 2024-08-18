#include "so_long.h"

void	key_hook_helper(int keysym, t_var *data)
{
	if (data->playery + 1 != data->map->height - 1
		&& data->amap[data->playery + 1][data->playerx] != '1'
		&& keysym == XK_s)
	{
		if (hook_handler(data, data->playery + 1, data->playerx))
			return ;
		data->playery++;
	}
	if (data->playerx + 1 != data->map->width - 1
		&& data->amap[data->playery][data->playerx + 1] != '1'
		&& keysym == XK_d)
	{
		if (hook_handler(data, data->playery, data->playerx + 1))
			return ;
		data->playerx++;
	}
}

int	key_hook(int keysym, t_var *data)
{
	if (keysym == XK_Escape)
		close_window(data);
	if (data->playery - 1 != 0
		&& data->amap[data->playery - 1][data->playerx] != '1'
		&& keysym == XK_w)
	{
		if ((hook_handler(data, data->playery - 1, data->playerx)))
			return (1);
		data->playery--;
	}
	if (data->playerx - 1 != 0
		&& data->amap[data->playery][data->playerx - 1] != '1'
		&& keysym == XK_a)
	{
		if (hook_handler(data, data->playery, data->playerx - 1))
			return (1);
		data->playerx--;
	}
	key_hook_helper(keysym, data);
	render(data);
	return (0);
}

int	close_window(t_var *data)
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

int	load_textures(t_var *data)
{
	data->textures[0] = xpm_image(data, "textures/hedge.xpm");
	if (!data->textures[0])
		return (ft_putstr_fd("Failed to load textures/headge.xpm", 2), 1);
	data->textures[1] = xpm_image(data, "textures/portal.xpm");
	if (!data->textures[1])
		return (ft_putstr_fd("Failed to load textures/portal.xpm", 2), 1);
	data->textures[2] = xpm_image(data, "textures/background.xpm");
	if (!data->textures[2])
		return (ft_putstr_fd("Failed to load textures/background.xpm", 2), 1);
	data->textures[3] = xpm_image(data, "textures/mainchar.xpm");
	if (!data->textures[3])
		return (ft_putstr_fd("Failed to load textures/mainchar.xpm", 2), 1);
	data->textures[4] = xpm_image(data, "textures/rose.xpm");
	if (!data->textures[4])
		return (ft_putstr_fd("Failed to load textures/rose.xpm", 2), 1);
	return (0);
}

int	visual( t_map *map)
{
	t_var	data;

	data = (t_var){0};
	load_data(&data, map);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (close_window(&data), 1);
	data.win = mlx_new_window(data.mlx, map->width * 32, \
		map->height * 32, "so_long");
	if (!data.win)
		return (close_window(&data), 1);
	if (load_textures(&data))
		return (close_window(&data), 1);
	render (&data);
	mlx_put_image_to_window(data.mlx, data.win, \
		data.textures[3], data.x, data.y);
	mlx_hook(data.win, DestroyNotify, \
		StructureNotifyMask, &close_window, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
