/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:29:29 by dfasius           #+#    #+#             */
/*   Updated: 2024/08/19 18:29:30 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
	data->direction = BACK;
	data->x = map->playerx * 32;
	data->y = map->playery * 32;
	data->playerx = map->playerx;
	data->playery = map->playery;
	data->amap = map->amap;
}

void	key_hook_helper(int keysym, t_var *data)
{
	if (data->playery + 1 != data->map->height - 1
		&& data->amap[data->playery + 1][data->playerx] != '1'
		&& keysym == XK_s && !data->is_moving)
	{
		if (hook_handler(data, data->playery + 1, data->playerx))
			return ;
		key_handler(data, 2);
	}
	if (data->playerx + 1 != data->map->width - 1
		&& data->amap[data->playery][data->playerx + 1] != '1'
		&& keysym == XK_d && !data->is_moving)
	{
		if (hook_handler(data, data->playery, data->playerx + 1))
			return ;
		key_handler(data, 3);
	}
}
