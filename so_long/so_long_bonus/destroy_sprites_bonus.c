#include "so_long_bonus.h"

void	destroy_texture(t_var *data)
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
	if (data->mlx && data->textures[5])
		mlx_destroy_image(data->mlx, data->textures[5]);
}

void	destroy_sprites(t_var *data)
{
	if (data->mlx && data->sprites[0][0])
		mlx_destroy_image(data->mlx, data->sprites[0][0]);
	if (data->mlx && data->sprites[0][1])
		mlx_destroy_image(data->mlx, data->sprites[0][1]);
	if (data->mlx && data->sprites[0][2])
		mlx_destroy_image(data->mlx, data->sprites[0][2]);
	if (data->mlx && data->sprites[0][3])
		mlx_destroy_image(data->mlx, data->sprites[0][3]);
	if (data->mlx && data->sprites[1][0])
		mlx_destroy_image(data->mlx, data->sprites[1][0]);
	if (data->mlx && data->sprites[1][1])
		mlx_destroy_image(data->mlx, data->sprites[1][1]);
	if (data->mlx && data->sprites[1][2])
		mlx_destroy_image(data->mlx, data->sprites[1][2]);
	if (data->mlx && data->sprites[1][3])
		mlx_destroy_image(data->mlx, data->sprites[1][3]);
	destroy_sprites_helper(data);
}

void	destroy_sprites_helper(t_var *data)
{
	if (data->mlx && data->sprites[2][0])
		mlx_destroy_image(data->mlx, data->sprites[2][0]);
	if (data->mlx && data->sprites[2][1])
		mlx_destroy_image(data->mlx, data->sprites[2][1]);
	if (data->mlx && data->sprites[2][2])
		mlx_destroy_image(data->mlx, data->sprites[2][2]);
	if (data->mlx && data->sprites[2][3])
		mlx_destroy_image(data->mlx, data->sprites[2][3]);
	if (data->mlx && data->sprites[3][0])
		mlx_destroy_image(data->mlx, data->sprites[3][0]);
	if (data->mlx && data->sprites[3][1])
		mlx_destroy_image(data->mlx, data->sprites[3][1]);
	if (data->mlx && data->sprites[3][2])
		mlx_destroy_image(data->mlx, data->sprites[3][2]);
	if (data->mlx && data->sprites[3][3])
		mlx_destroy_image(data->mlx, data->sprites[3][3]);
}
