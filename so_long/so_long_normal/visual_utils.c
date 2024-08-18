#include "so_long.h"

void	draw_image(t_var *data, void *img, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->win, img, x, y);
}

void	*xpm_image(t_var *data, char *path)
{
	return (mlx_xpm_file_to_image(data->mlx, path, \
			&data->texture_length, &data->texture_length));
}

void	load_data(t_var *data, t_map *map)
{
	data->map = map;
	data->x = map->playerx * 32;
	data->y = map->playery * 32;
	data->playerx = map->playerx;
	data->playery = map->playery;
	data->amap = map->amap;
}
