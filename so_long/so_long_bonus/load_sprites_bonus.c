#include "so_long_bonus.h"

int	load_sprites_front(t_var *data)
{
	data->sprites[0][0] = xpm_image(data, "textures/char/front/front1.xpm");
	if (!data->sprites[0][0])
	{
		ft_putstr_fd("Failed to load textures/char/front/front1.xpm", 2);
		return (1);
	}
	data->sprites[0][1] = xpm_image(data, "textures/char/front/front2.xpm");
	if (!data->sprites[0][1])
	{
		ft_putstr_fd("Failed to load textures/char/front/front2.xpm", 2);
		return (1);
	}
	data->sprites[0][2] = xpm_image(data, "textures/char/front/front3.xpm");
	if (!data->sprites[0][2])
	{
		ft_putstr_fd("Failed to load textures/char/front/front3.xpm", 2);
		return (1);
	}
	data->sprites[0][3] = xpm_image(data, "textures/char/front/front4.xpm");
	if (!data->sprites[0][3])
	{
		ft_putstr_fd("Failed to load textures/char/front/front4.xpm", 2);
		return (1);
	}
	return (0);
}

int	load_sprites_back(t_var *data)
{
	data->sprites[1][0] = xpm_image(data, "textures/char/back/back1.xpm");
	if (!data->sprites[1][0])
	{
		ft_putstr_fd("Failed to load textures/char/back/back1.xpm", 2);
		return (1);
	}
	data->sprites[1][1] = xpm_image(data, "textures/char/back/back2.xpm");
	if (!data->sprites[1][1])
	{
		ft_putstr_fd("Failed to load textures/char/back/back2.xpm", 2);
		return (1);
	}
	data->sprites[1][2] = xpm_image(data, "textures/char/back/back3.xpm");
	if (!data->sprites[1][2])
	{
		ft_putstr_fd("Failed to load textures/char/back/back3.xpm", 2);
		return (1);
	}
	data->sprites[1][3] = xpm_image(data, "textures/char/back/back4.xpm");
	if (!data->sprites[1][3])
	{
		ft_putstr_fd("Failed to load textures/char/back/back4.xpm", 2);
		return (1);
	}
	return (0);
}

int	load_sprites_right(t_var *data)
{
	data->sprites[2][0] = xpm_image(data, "textures/char/right/right1.xpm");
	if (!data->sprites[2][0])
	{
		ft_putstr_fd("Failed to load textures/char/right/right1.xpm", 2);
		return (1);
	}
	data->sprites[2][1] = xpm_image(data, "textures/char/right/right2.xpm");
	if (!data->sprites[2][1])
	{
		ft_putstr_fd("Failed to load textures/char/right/right2.xpm", 2);
		return (1);
	}
	data->sprites[2][2] = xpm_image(data, "textures/char/right/right3.xpm");
	if (!data->sprites[2][2])
	{
		ft_putstr_fd("Failed to load textures/char/right/right3.xpm", 2);
		return (1);
	}
	data->sprites[2][3] = xpm_image(data, "textures/char/right/right4.xpm");
	if (!data->sprites[2][3])
	{
		ft_putstr_fd("Failed to load textures/char/right/right4.xpm", 2);
		return (1);
	}
	return (0);
}

int	load_sprites_left(t_var *data)
{
	data->sprites[3][0] = xpm_image(data, "textures/char/left/left1.xpm");
	if (!data->sprites[3][0])
	{
		ft_putstr_fd("Failed to load textures/char/left/left1.xpm", 2);
		return (1);
	}
	data->sprites[3][1] = xpm_image(data, "textures/char/left/left2.xpm");
	if (!data->sprites[3][1])
	{
		ft_putstr_fd("Failed to load textures/char/left/left2.xpm", 2);
		return (1);
	}
	data->sprites[3][2] = xpm_image(data, "textures/char/left/left3.xpm");
	if (!data->sprites[3][2])
	{
		ft_putstr_fd("Failed to load textures/char/left/left3.xpm", 2);
		return (1);
	}
	data->sprites[3][3] = xpm_image(data, "textures/char/left/left4.xpm");
	if (!data->sprites[3][3])
	{
		ft_putstr_fd("Failed to load textures/char/left/left4.xpm", 2);
		return (1);
	}
	return (0);
}

int	load_sprites(t_var *data)
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
