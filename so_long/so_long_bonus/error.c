#include "so_long.h"

void    handle_error(char *error)
{
    perror(error);
    exit(0);
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