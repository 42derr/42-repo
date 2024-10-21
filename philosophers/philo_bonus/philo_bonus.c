/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:45:11 by dfasius           #+#    #+#             */
/*   Updated: 2024/10/22 04:50:14 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	handle_exit(t_phil *phil, t_update *updatem)
{
	if (phil->should_die == 1)
	{
		error_handler(NULL, phil, updatem);
		exit(1);
	}
	else
	{
		error_handler(NULL, phil, updatem);
		exit(0);
	}
}

int	create_process(t_phil *phil, int nphil, t_update update, t_update *updatem)
{
	pid_t		pid;
	pthread_t	death_checker;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (update.cur_phil % 2 == 0 && phil->num_phil > 1)
		{
			usleep(phil->time_eat * 1000);
			if (phil->num_phil % 2 == 1
				&& (update.cur_phil + 1 == phil->num_phil))
				usleep(phil->time_eat * 1000);
		}
		pthread_create(&death_checker, NULL, &check_die, &update);
		do_routine(&update, phil, nphil);
		pthread_join(death_checker, NULL);
		handle_exit(phil, updatem);
	}
	else
		phil->phil_pid[nphil] = pid;
	return (0);
}

void	create_child(t_phil *phil, t_update *update)
{
	int	i;

	i = 0;
	while (i < phil->num_phil)
	{
		create_process(phil, i, update[i], update);
		i++;
	}
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

int	main(int argc, char *argv[])
{
	t_phil		phil;
	t_update	*update;

	if (argc < 5 || argc > 6)
		return (printf("./philo_bonus [number_of_philosophers] [time_to_die]"
				" [time_to_eat] [time_to_sleep] "
				"[number_of_times_each_philosopher_must_eat]\n"), 1);
	if (init_phil(&phil, argc, argv))
		return (1);
	if (init_sem(&phil))
		return (1);
	update = init_update(&phil);
	if (!update)
		return (error_handler("malloc error on update", &phil, NULL), 1);
	create_child(&phil, update);
	wait_child(&phil);
	error_handler(NULL, &phil, update);
	return (0);
}
