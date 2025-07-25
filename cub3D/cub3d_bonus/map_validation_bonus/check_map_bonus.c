/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:45:45 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:45:47 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	validate_map_char(t_map *map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map->arr[i])
	{
		j = 0;
		while (map->arr[i][j])
		{
			if (!(ft_strchr(" 01NSEW\n", map->arr[i][j])))
				handle_error("The map must be composed \
					of only 0, 1, N, S, E, W", NULL, map, NULL);
			if (ft_strchr("NSEW", map->arr[i][j]))
			{
				map->xpos = j;
				map->ypos = i;
				player++;
			}
			j++;
		}
		i++;
	}
	validate_player(map, player);
}

void	check_surrounding(t_map *map, int y, int x)
{
	char	left;
	char	right;
	char	up;
	char	down;

	if (x == 0 || x == map->max_length - 1
		|| y == 0 || y == map->height - 1)
		handle_error("The map must be surrounded by walls", NULL, map, NULL);
	left = map->arr[y - 1][x];
	right = map->arr[y + 1][x];
	up = map->arr[y][x - 1];
	down = map->arr[y][x + 1];
	if (left == 'X' || right == 'X' || up == 'X' || down == 'X'
		|| left == '\n' || right == '\n' || up == '\n' || down == '\n')
		handle_error("The map must be surrounded by walls", NULL, map, NULL);
}

void	change_player(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->arr[y])
	{
		x = 0;
		while (map->arr[y][x])
		{
			if (ft_strchr("NSEW", map->arr[y][x]))
			{
				map->start_dir = map->arr[y][x];
				map->arr[y][x] = EMPTY_SPACE;
			}
			x++;
		}
		y++;
	}
}

void	check_wall(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->arr[y])
	{
		x = 0;
		while (map->arr[y][x])
		{
			if (map->arr[y][x] == EMPTY_SPACE
				|| ft_strchr("NSEW", map->arr[y][x]))
				check_surrounding(map, y, x);
			x++;
		}
		y++;
	}
}

void	check_map(t_map *map)
{
	validate_map_char(map);
	find_max_row_length(map);
	replace_space(map);
	check_wall(map);
	change_player(map);
}
