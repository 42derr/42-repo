/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:43:41 by dfasius           #+#    #+#             */
/*   Updated: 2024/10/21 20:25:32 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
			sem_wait(update->phil->sem_check);
			if (update->phil->eaten == 0)
			{
				sem_wait(update->phil->sem_die);
				log_change(update->phil, update->cur_phil + 1, 5);
				exit (1);
			}
			else
				update->phil->eaten = 0;
			sem_post(update->phil->sem_check);
			start = cur;
		}
	}
	return (NULL);
}

void	wait_child(t_phil *phil)
{
	int	i;
	int	exitcode;
	int	status;
	int	x;

	x = 0;
	while (x < phil->num_phil)
	{
		waitpid(-1, &status, 0);
		exitcode = status >> 8;
		if (exitcode == 1)
		{
			i = 0;
			while (i < phil->num_phil)
				kill(phil->phil_pid[i++], SIGKILL);
			return ;
		}
		x++;
	}
}

int	do_routine(t_update *update, t_phil *phil, int nphil)
{
	sem_wait(phil->sem_take_fork);
	sem_wait(phil->sem_fork);
	log_change(phil, nphil + 1, 1);
	if (phil->num_phil == 1)
		return (sem_post(phil->sem_check), 1);
	sem_wait(phil->sem_fork);
	log_change(phil, nphil + 1, 1);
	sem_post(phil->sem_take_fork);
	log_change(phil, nphil + 1, 2);
	usleep(phil->time_eat * 1000);
	sem_post(phil->sem_fork);
	sem_post(phil->sem_fork);
	update->total_eat++;
	sem_wait(phil->sem_check);
	phil->eaten = 1;
	sem_post(phil->sem_check);
	if (phil->num_eat != -1 && update->total_eat == phil->num_eat)
		exit (0);
	log_change(phil, nphil + 1, 3);
	usleep(phil->time_sleep * 1000);
	usleep(300);
	log_change(phil, nphil + 1, 4);
	return (0);
}
