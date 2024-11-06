/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 00:54:48 by dfasius           #+#    #+#             */
/*   Updated: 2024/11/01 14:11:21 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	error_handler(char *buffer, t_phil *phil, t_update *update)
{
	if (phil && phil->fork_state)
		free(phil->fork_state);
	if (phil && phil->last_time)
		free(phil->last_time);
	if (phil && phil->thread)
		free(phil->thread);
	if (update)
		free(update);
	if (buffer)
		printf("%s\n", buffer);
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

void	handle_delay(t_update *update)
{
	if (update->cur_phil % 2 == 0 && update->phil->num_phil > 1)
	{
		log_change(update->phil, update->cur_phil + 1, 4);
		usleep(update->phil->time_eat * 1000);
		if (update->cur_phil == update->phil->num_phil - 1)
			usleep(update->phil->time_eat * 1000);
	}
}
