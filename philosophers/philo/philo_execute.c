/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 01:21:24 by dfasius           #+#    #+#             */
/*   Updated: 2024/10/22 04:45:32 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_update *update, int firstfork, int secondfork)
{
	struct timeval	tv;

	if (update->phil->die)
		return (pthread_mutex_unlock(&update->phil->lock), 1);
	if (update->phil->fork_state[firstfork] == 0
		&& update->phil->fork_state[secondfork] == 0
		&& !update->phil->die && should_eat(update))
	{
		update->phil->fork_state[firstfork] = 1;
		log_change(update->phil, update->cur_phil + 1, 1);
		if (update->phil->num_phil == 1)
			return (pthread_mutex_unlock(&update->phil->lock), 1);
		update->phil->fork_state[secondfork] = 1;
		log_change(update->phil, update->cur_phil + 1, 1);
		log_change(update->phil, update->cur_phil + 1, 2);
		gettimeofday(&tv, NULL);
		update->last_eat = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		update->phil->last_time[update->cur_phil] = update->last_eat;
		update->eating = 1;
		update->total_eat++;
		if (update->total_eat == update->phil->num_eat
			&& update->phil->num_eat != -1)
			update->phil->finish++;
	}
	return (0);
}

int	philo_think(t_update *update, int firstfork, int secondfork)
{
	if (update->phil->time_eat > update->phil->time_die)
		return (1);
	usleep(update->phil->time_eat * 1000);
	pthread_mutex_lock(&update->phil->lock);
	update->phil->fork_state[firstfork] = 0;
	update->phil->fork_state[secondfork] = 0;
	if (update->phil->die)
		return (pthread_mutex_unlock(&update->phil->lock), 1);
	if (update->phil->finish >= update->phil->num_phil - 1)
		return (pthread_mutex_unlock(&update->phil->lock), 1);
	log_change(update->phil, update->cur_phil + 1, 3);
	pthread_mutex_unlock(&update->phil->lock);
	if (update->phil->time_eat + update->phil->time_sleep
		> update->phil->time_die)
		return (1);
	usleep(update->phil->time_sleep * 1000);
	pthread_mutex_lock(&update->phil->lock);
	if (update->phil->die)
		return (pthread_mutex_unlock(&update->phil->lock), 1);
	if (update->total_eat == update->phil->num_eat
		&& update->phil->num_eat != -1)
		return (pthread_mutex_unlock(&update->phil->lock), 1);
	log_change(update->phil, update->cur_phil + 1, 4);
	update->eating = 0;
	return (pthread_mutex_unlock(&update->phil->lock), 0);
}

void	*process_activity(void *args)
{
	int			firstfork;
	int			secondfork;
	t_update	*update;

	update = (t_update *) args;
	firstfork = update->cur_phil - 1;
	if (firstfork == -1)
		firstfork = update->phil->num_phil - 1;
	secondfork = update->cur_phil;
	while ((update->total_eat != update->phil->num_eat)
		|| update->phil->num_eat == -1)
	{
		pthread_mutex_lock(&update->phil->lock);
		if (philo_eat(update, firstfork, secondfork))
			return (NULL);
		pthread_mutex_unlock(&update->phil->lock);
		if (update->eating == 1)
			if (philo_think(update, firstfork, secondfork))
				return (NULL);
	}
	return (NULL);
}

int	check_death_helper(t_update *update, int i)
{
	struct timeval	tv;
	long			cur_time;

	gettimeofday(&tv, NULL);
	cur_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (cur_time == 0)
		return (1);
	pthread_mutex_lock (&update[0].phil->lock);
	if (update->phil->finish == update->phil->num_phil)
		return (pthread_mutex_unlock (&update[0].phil->lock), 1);
	if (((int)(cur_time - update[i].last_eat)) > update[0].phil->time_die)
	{
		log_change(update[i].phil, update[i].cur_phil + 1, 5);
		update[0].phil->die = 1;
		return (pthread_mutex_unlock (&update[0].phil->lock), 1);
	}
	pthread_mutex_unlock (&update[0].phil->lock);
	return (0);
}

void	*check_death(void *args)
{
	t_update	*update;
	int			i;

	i = 0;
	update = (t_update *) args;
	while (1)
	{
		i = 0;
		while (i < update[0].phil->num_phil)
		{
			if (check_death_helper(update, i))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
