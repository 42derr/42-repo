/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:13:35 by dfasius           #+#    #+#             */
/*   Updated: 2024/07/31 18:10:47 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
# include "llist.h"
#include <stdio.h>

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

typedef struct s_map {
    struct s_list *map_lst;
    int height;
    int width;
    int exit;
    int start;
    int collectible;
    int playery;
    int playerx;
} t_map;

#define SIDE_LEN 416
#define NUM_SPIKES 5
#define HEDGE_SIZE 32

typedef struct s_img
{
    void    *img_ptr;
    char    *img_pixels_ptr;
    int     bits_per_pixel;
    int     endian;
    int     line_len;
}               t_img;

typedef struct s_var
{
    void    *mlx;
    void    *win;
    t_img   img;
    void    *hedge_img;
    void    *portal_img;
    void    *calf_img;
    void    *rose_img;
    void    *wood_img;
    t_map *map;
}               t_var;


void    read_map(t_map *map, int fd);

int visual(int width, int height, t_map *map);
int     key_hook(int keysym, t_var *data);
void    draw_random_images(t_var *data, t_map *map);
void    draw_edges(t_var *data);
void    draw_image(t_var *data, void *img, int x, int y);

void w_move(t_map *map);
void a_move(t_map *map);
void s_move(t_map *map);
void d_move(t_map *map);

#endif
