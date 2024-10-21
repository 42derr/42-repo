/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 00:59:59 by dfasius           #+#    #+#             */
/*   Updated: 2024/10/21 19:24:35 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_change(t_phil *phil, int nphil, int cur)
{
	struct timeval	tv;
	long			cur_time;
	long			timestamp;

	gettimeofday(&tv, NULL);
	cur_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	timestamp = cur_time - phil->start_time;
	if (cur == 1)
		printf("%ld %d has taken a fork\n", timestamp, nphil);
	else if (cur == 2)
		printf("%ld %d is eating\n", timestamp, nphil);
	else if (cur == 3)
		printf("%ld %d is sleeping\n", timestamp, nphil);
	else if (cur == 4)
		printf("%ld %d is thinking\n", timestamp, nphil);
	else if (cur == 5)
		printf("%ld %d died\n", timestamp, nphil);
}

int	should_eat(t_update *update)
{
	int		i;
	long	min;

	i = 0;
	if (update->total_eat == 0)
		return (1);
	min = update->phil->last_time[update->cur_phil];
	while (i < update->phil->num_phil)
	{
		if (min > update->phil->last_time[i])
			return (0);
		i++;
	}
	return (1);
}

t_update	*init_update(t_phil *phil)
{
	t_update	*update;
	int			i;

	i = 0;
	update = (t_update *) malloc (sizeof(t_update) * phil->num_phil);
	if (!update)
		return (NULL);
	while (i < phil->num_phil)
	{
		update[i].phil = phil;
		update[i].cur_phil = i;
		update[i].eating = 0;
		update[i].last_eat = phil->start_time;
		update[i].total_eat = 0;
		i++;
	}
	return (update);
}

int	init_phil_helper(t_phil *phil)
{
	int				i;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	phil->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	phil->fork_state = (int *) malloc (sizeof(int) * phil->num_phil);
	if (!phil->fork_state)
		return (error_handler("error on fork_state", NULL, NULL), 1);
	i = 0;
	while (i < phil->num_phil)
	{
		phil->fork_state[i] = 0;
		i++;
	}
	phil->last_time = (long *) malloc (sizeof(long) * phil->num_phil);
	if (!phil->last_time)
		return (error_handler("error on phil->last_time", phil, NULL), 1);
	i = 0;
	while (i < phil->num_phil)
	{
		phil->last_time[i] = 0;
		i++;
	}
	return (0);
}

int	init_phil(t_phil *phil, int argc, char **argv)
{
	if (check_non_number(argv))
		return (1);
	phil->num_phil = ft_atoi(argv[1]);
	phil->time_die = ft_atoi(argv[2]);
	phil->time_eat = ft_atoi(argv[3]);
	phil->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		phil->num_eat = ft_atoi(argv[5]);
		if (phil->num_eat <= 0)
			return (printf("Args must be non-negative and non-zero\n"), 1);
	}
	else
		phil->num_eat = -1;
	if (phil->num_phil <= 0 || phil->time_die <= 0
		|| phil->time_eat <= 0 || phil->time_sleep <= 0)
		return (printf("Args must be non-negative and non-zero\n"), 1);
	if (init_phil_helper(phil))
		return (1);
	return (0);
}
