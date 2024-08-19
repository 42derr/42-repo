/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:29:49 by dfasius           #+#    #+#             */
/*   Updated: 2024/08/19 18:29:51 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

bool	**generate_visited(t_map *map)
{
	bool	**visited;
	bool	*buffer;
	int		j;
	int		i;

	j = 0;
	i = 0;
	visited = (bool **) malloc (sizeof(bool *) * map->height);
	if (!visited)
		return (NULL);
	while (j < map->height)
	{
		buffer = (bool *) malloc (sizeof(bool) * map->width);
		if (!buffer)
			return (free_bool(visited, j), NULL);
		i = 0;
		while (i < map->width)
		{
			buffer[i] = false;
			i++;
		}
		visited[j] = buffer;
		j++;
	}
	return (visited);
}

void	generate_arraymap(t_map *map)
{
	t_list	*maplist;
	char	*buffer;
	char	*new;

	maplist = map->map_lst;
	buffer = ft_strdup("");
	if (!buffer)
		return ;
	while (maplist)
	{
		new = ft_strjoin(buffer, ";");
		free(buffer);
		if (!new)
			return ;
		buffer = ft_strjoin(new, (char *) maplist->content);
		free(new);
		if (!buffer)
			return ;
		maplist = maplist->next;
	}
	map->amap = ft_split(buffer, ';');
	free(buffer);
}
