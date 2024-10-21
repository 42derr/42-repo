/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:02:55 by dfasius           #+#    #+#             */
/*   Updated: 2024/10/21 19:41:49 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		cm;
	int		i;

	cm = c % 256;
	str = (char *) s;
	i = 0;
	while (s[i] != cm && s[i] != '\0')
		i++;
	if (s[i] == cm)
		return (str + i);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	long	i;
	long	s;
	long	m;

	i = 0;
	m = 1;
	s = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			m = m * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		s = s * 10 + (nptr[i] - 48);
		i++;
	}
	s = s * m;
	if (s <= 2147483647 && s >= -2147483648)
		return ((int)s);
	return (0);
}

int	check_non_number(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_strchr("0123456789", argv[i][j]))
				return (printf("There is a non number in args\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

void	error_handler(char *buffer, t_phil *phil, t_update *update)
{
	if (phil && phil->phil_pid)
		free(phil->phil_pid);
	if (update)
		free(update);
	if (buffer)
		printf("%s\n", buffer);
	if (phil->sem_take_fork)
		sem_close(phil->sem_take_fork);
	if (phil->sem_fork)
		sem_close(phil->sem_fork);
	if (phil->sem_die)
		sem_close(phil->sem_die);
	if (phil->sem_check)
		sem_close(phil->sem_check);
}

long	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
