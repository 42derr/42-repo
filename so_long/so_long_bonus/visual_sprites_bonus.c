/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_sprites_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:29:34 by dfasius           #+#    #+#             */
/*   Updated: 2024/08/23 09:32:53 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	close_window(t_var *data)
{
	destroy_texture(data);
	destroy_sprites(data);
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
	if (data->amap)
		free_array(data->amap);
	exit(1);
	return (0);
}

int	load_textures(t_var *data)
{
	data->textures[0] = xpm_image(data, "textures/hedge.xpm");
	if (!data->textures[0])
		return (tex_err("Failed to load textures/headge.xpm"), 1);
	data->textures[1] = xpm_image(data, "textures/portal.xpm");
	if (!data->textures[1])
		return (tex_err("Failed to load textures/portal.xpm"), 1);
	data->textures[2] = xpm_image(data, "textures/background.xpm");
	if (!data->textures[2])
		return (tex_err("Failed to load textures/background.xpm"), 1);
	data->textures[3] = xpm_image(data, "textures/mainchar.xpm");
	if (!data->textures[3])
		return (tex_err("Failed to load textures/mainchar.xpm"), 1);
	data->textures[4] = xpm_image(data, "textures/rose.xpm");
	if (!data->textures[4])
		return (tex_err("Failed to load textures/rose.xpm"), 1);
	data->textures[5] = xpm_image(data, "textures/ghost.xpm");
	if (!data->textures[5])
		return (tex_err("Failed to load textures/ghost.xpm"), 1);
	if (load_sprites(data))
		return (1);
	return (0);
}
