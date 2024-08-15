#include "so_long.h"

void    map_err(t_map *map, char *buffer, char *err, char *str_err)
{
    ft_putstr_fd("Error\n", 2);
    if (err)
        perror(err);
    if (str_err)
        ft_putstr_fd(str_err, 2);
    if (map && map->map_lst)
        ft_lstclear(&map->map_lst, &free);
    if (buffer)
        free(buffer);
    exit (1);
}

void	free_array(char	**buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
}

void	free_bool(bool	**buffer, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
}