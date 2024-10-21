/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:00:48 by dfasius           #+#    #+#             */
/*   Updated: 2024/10/21 19:40:49 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	init_phil_helper(t_phil *phil)
{
	int				i;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	phil->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	phil->phil_pid = (pid_t *) malloc (sizeof(pid_t) * phil->num_phil);
	if (!phil->phil_pid)
		return (printf("malloc error on phil->phild_pid\n"), 1);
	i = 0;
	while (i < phil->num_phil)
	{
		phil->phil_pid[i] = 0;
		i++;
	}
	return (0);
}

int	init_phil(t_phil *phil, int argc, char *argv[])
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
		update[i].total_eat = 0;
		update[i].cur_phil = i;
		i++;
	}
	return (update);
}

int	init_sem(t_phil *phil)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_TAKE_FORK);
	sem_unlink(SEM_DIE);
	sem_unlink(SEM_CHECK);
	phil->sem_fork = sem_open(SEM_FORK, O_CREAT, 0660, phil->num_phil);
	if (phil->sem_fork == SEM_FAILED)
		return (error_handler("sem/fork", phil, NULL), 1);
	phil->sem_take_fork = sem_open(SEM_TAKE_FORK, O_CREAT, 0660, 1);
	if (phil->sem_take_fork == SEM_FAILED)
		return (error_handler("sem/take_fork", phil, NULL), 1);
	phil->sem_die = sem_open(SEM_DIE, O_CREAT, 0660, 1);
	if (phil->sem_die == SEM_FAILED)
		return (error_handler("sem/die", phil, NULL), 1);
	phil->sem_check = sem_open(SEM_CHECK, O_CREAT, 0660, 1);
	if (phil->sem_check == SEM_FAILED)
		return (error_handler("sem/check", phil, NULL), 1);
	return (0);
}
