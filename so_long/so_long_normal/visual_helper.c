#include "so_long.h"

void	render(t_var *data)
{
	draw_textures(data, data->map);
	display_move(data);
	data->y = data->playery * 32;
	data->x = data->playerx * 32;
	draw_image(data, data->textures[3], data->x, data->y);
}

void	draw_textures_helper(t_var *data, t_map *map, int i, int y)
{
	int	j;
	int	x;

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
		j++;
		x += 32;
	}
}

void	draw_textures(t_var *data, t_map *map)
{
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (data->amap[i])
	{
		draw_textures_helper(data, map, i, y);
		i++;
		y += 32;
	}
}

int	hook_handler(t_var *data, int y, int x)
{
	if (data->amap[y][x] == 'E')
	{
		if (data->map->collectible != 0)
		{
			ft_putstr_fd("Collect all collectable !\n", 1);
			return (1);
		}
		else
			close_window(data);
	}
	data->move++;
	if (data->amap[y][x] == 'C')
	{
		data->map->collectible--;
		data->amap[y][x] = '0';
	}
	return (0);
}
