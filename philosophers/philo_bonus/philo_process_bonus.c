/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:43:41 by dfasius           #+#    #+#             */
/*   Updated: 2024/11/01 14:05:37 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_die_helper(t_update *update)
{
	sem_wait(update->phil->sem_check);
	if (update->phil->eaten == 0)
	{
		sem_wait(update->phil->sem_die);
		update->phil->should_die = 1;
		log_change(update->phil, update->cur_phil + 1, 5);
		return (1);
	}
	else
		update->phil->eaten = 0;
	sem_post(update->phil->sem_check);
	return (0);
}

void	*check_die(void *args)
{
	long		cur;
	long		start;
	t_update	*update;

	update = (t_update *)args;
	start = update->phil->start_time;
	while (1)
	{
		cur = ft_time();
		if (cur - start >= update->phil->time_die)
		{
			if (check_die_helper(update))
				break ;
			start = cur;
		}
		sem_wait(update->phil->sem_check);
		if (update->phil->should_exit)
			break ;
		sem_post(update->phil->sem_check);
	}
	return (sem_post(update->phil->sem_check), NULL);
}

int	not_survive(long last, long time, t_phil *phil)
{
	long	cur;

	cur = ft_time();
	if (cur - last + time >= phil->time_die)
		return (1);
	return (0);
}

int	do_routine(t_update *update, t_phil *phil, int nphil)
{
	while (1)
	{
		if (do_routine_helper(update, phil, nphil))
			break ;
		update->last_eat = ft_time();
		sem_wait(phil->sem_check);
		if (phil->num_eat != -1 && update->total_eat == phil->num_eat)
		{
			phil->should_exit = 1;
			return (sem_post(phil->sem_check), 0);
		}
		sem_post(phil->sem_check);
		sem_wait(phil->sem_check);
		if (phil->should_die
			|| not_survive(update->last_eat, phil->time_sleep, phil))
		{
			sem_post(phil->sem_check);
			break ;
		}
		sem_post(phil->sem_check);
		log_change(phil, nphil + 1, 3);
		usleep((phil->time_sleep * 1000) + 500);
		log_change(phil, nphil + 1, 4);
	}
	return (0);
}

int	do_routine_helper(t_update *update, t_phil *phil, int nphil)
{
	sem_wait(phil->sem_take_fork);
	sem_wait(phil->sem_fork);
	log_change(phil, nphil + 1, 1);
	if (phil->num_phil == 1)
		return (1);
	sem_wait(phil->sem_fork);
	log_change(phil, nphil + 1, 1);
	sem_post(phil->sem_take_fork);
	sem_wait(phil->sem_check);
	if (phil->should_die
		|| not_survive(update->last_eat, phil->time_eat, phil))
	{
		sem_post(phil->sem_check);
		return (1);
	}
	sem_post(phil->sem_check);
	log_change(phil, nphil + 1, 2);
	usleep(phil->time_eat * 1000);
	sem_post(phil->sem_fork);
	sem_post(phil->sem_fork);
	update->total_eat++;
	sem_wait(phil->sem_check);
	phil->eaten = 1;
	sem_post(phil->sem_check);
	return (0);
}
