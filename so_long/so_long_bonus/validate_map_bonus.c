/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:30:14 by dfasius           #+#    #+#             */
/*   Updated: 2024/08/19 18:34:55 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

bool	run_map(int x, int y, t_map *map)
{
	if (x < 0 || x >= map->width
		|| y < 0 || y >= map->height
		|| map->visited[y][x] == true
		|| map->amap[y][x] == '1')
		return (false);
	map->visited[y][x] = true;
	if (map->amap[y][x] == 'C')
		map->valid_col--;
	else if (map->amap[y][x] == 'E')
		map->valid_exit--;
	if (map->valid_col == 0 && map->valid_exit == 0)
		return (true);
	return (run_map(x + 1, y, map)
		|| run_map(x - 1, y, map)
		|| run_map(x, y + 1, map)
		|| run_map(x, y - 1, map));
}

bool	validate_map(t_map *map)
{
	bool	path_found;
	bool	path_valid;

	map->valid_col = map->collectible;
	map->valid_exit = map->exit;
	generate_arraymap(map);
	if (!map->amap)
		return (false);
	map->visited = generate_visited(map);
	if (!map->visited)
		return (free_array(map->amap), false);
	path_found = run_map(map->playerx, map->playery, map);
	if (path_found && map->valid_col == 0 && map->valid_exit == 0)
		path_valid = true;
	else
		path_valid = false;
	free_bool(map->visited, map->height);
	return (path_valid);
}

bool	run_enemy(int x, int y, t_map *map)
{
	if (x < 0 || x >= map->width
		|| y < 0 || y >= map->height
		|| map->visited[y][x] == true || map->amap[y][x] == '1'
		|| map->amap[y][x] == 'X')
		return (false);
	map->visited[y][x] = true;
	if (map->amap[y][x] == 'C')
		map->valid_col--;
	else if (map->amap[y][x] == 'E')
		map->valid_exit--;
	if (map->valid_col == 0 && map->valid_exit == 0)
		return (true);
	return (run_enemy(x + 1, y, map)
		|| run_enemy(x - 1, y, map)
		|| run_enemy(x, y + 1, map)
		|| run_enemy(x, y - 1, map));
}

bool	validate_enemy(t_map *map)
{
	bool	path_found;
	bool	path_valid;

	map->valid_col = map->collectible;
	map->valid_exit = map->exit;
	map->visited = generate_visited(map);
	if (!map->visited)
		return (free_array(map->amap), false);
	path_found = run_enemy(map->playerx, map->playery, map);
	if (path_found && map->valid_col == 0 && map->valid_exit == 0)
		path_valid = true;
	else
		path_valid = false;
	free_bool(map->visited, map->height);
	return (path_valid);
}
