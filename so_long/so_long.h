/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:13:35 by dfasius           #+#    #+#             */
/*   Updated: 2024/08/06 19:18:06 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "list.h"
#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

#define SPRITE_SIZE 32
#define ANIMATION_DELAY 100000

typedef struct s_map {
    struct s_list *map_lst;
    char **amap;
    bool **visited;
    int height;
    int width;
    int exit;
    int start;
    int collectible;
    int valid_col;
    int playery;
    int playerx;
} t_map;

typedef struct s_var
{
	void		*mlx;
	void		*win;
	void		*textures[5];
	void		*sprites[4][4];
    char *string_move;
    int move;
    int         texture_length;
	t_map		*map;
}	t_var;

int    read_map(t_map *map, char *map_name);
void    map_info(t_map *map, t_list *maplist, int i);
int    check_map(t_map *map);

void    generate_arraymap(t_map *map);
bool    validate_map(t_map *map);
bool    **generate_visited(t_map *map);
bool    run_map(int x, int y, t_map *map);

int visual( t_map *map);
int     key_hook(int keysym, t_var *data);
void    draw_textures(t_var *data, t_map *map);
void    draw_image(t_var *data, void *img, int x, int y);
int close_window(t_var *data);

void    handle_error(char *error);
void	free_array(char	**buffer);
void	free_bool(bool	**buffer, int j);

void w_move(t_map *map, t_var *data);
void a_move(t_map *map, t_var *data);
void s_move(t_map *map, t_var *data);
void d_move(t_map *map, t_var *data);

void count_movement(t_var *data);
int num_len(int num);
void display_move(t_var *data);

int load_sprites_back(t_var *data);
int load_sprites_right(t_var *data);
int load_sprites_left(t_var *data);
int load_sprites_front(t_var *data);
int load_sprites(t_var *data);


#endif
