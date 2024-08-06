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