/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:13:35 by dfasius           #+#    #+#             */
/*   Updated: 2024/08/12 16:38:32 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../list.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# define SPRITE_SIZE 32
# define ANIMATION_DELAY 65000

typedef enum e_direction
{
	FRONT,
	BACK,
	RIGHT,
	LEFT
}	t_direction;

typedef struct s_map
{
	t_list	*map_lst;
	bool	**visited;
	char	**amap;
	int		playery;
	int		playerx;
	int		height;
	int		width;
	int		start;
	int		exit;
	int		valid_exit;
	int		collectible;
	int		valid_col;
}	t_map;

typedef struct s_var
{
	t_direction	direction;
	t_map		*map;
	time_t		last_update;
	char		*string_move;
	char		**amap;
	void		*mlx;
	void		*win;
	void		*textures[6];
	void		*sprites[4][4];
	int			move;
	int			texture_length;
	int			current_sprite;
	int			is_moving;
	int			playery;
	int			playerx;
	int			x;
	int			y;
}	t_var;

int		num_len(int num);
void	count_movement(t_var *data);
void	display_move(t_var *data);

void	map_err(t_map *map, char *buffer, char *err, char *str_err);
void	free_array(char	**buffer);
void	free_bool(bool	**buffer, int j);

int		load_sprites_front(t_var *data);
int		load_sprites_back(t_var *data);
int		load_sprites_right(t_var *data);
int		load_sprites_left(t_var *data);
int		load_sprites(t_var *data);

void	map_info(t_map *map, t_list *maplist, int i);
void	check_map_helper(t_map *map, t_list *maplist, int i);
void	check_map(t_map *map);

void	create_enemy(t_map *map);
int		clean_enemy(t_map *map);
void	check_name(char *name);
void	read_map(t_map *map, char *map_name);

bool	run_map(int x, int y, t_map *map);
bool	validate_map(t_map *map);
bool	run_enemy(int x, int y, t_map *map);
bool	validate_enemy(t_map *map);

bool	**generate_visited(t_map *map);
void	generate_arraymap(t_map *map);

void	render(t_var *game);
void	draw_textures_helper(t_var *data, t_map *map, int i, int y);
void	draw_textures(t_var *data, t_map *map);
int		hook_handler(t_var *data, int y, int x);

int		close_window(t_var *data);
int		load_textures(t_var *data);

int		update(t_var *game);
void	update_helper(t_var *game);
int		visual( t_map *map);
int		key_hook(int keysym, t_var *data);
void	key_handler(t_var *data, int i);

void	destroy_sprites(t_var *data);
void	destroy_texture(t_var *data);
void	destroy_sprites_helper(t_var *data);

void	*xpm_image(t_var *data, char *path);
void	draw_image(t_var *data, void *img, int x, int y);
void	load_data(t_var *data, t_map *map);
void	key_hook_helper(int keysym, t_var *data);

#endif
