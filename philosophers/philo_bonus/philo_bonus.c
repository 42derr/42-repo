/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:45:11 by dfasius           #+#    #+#             */
/*   Updated: 2024/10/21 20:27:17 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_process(t_phil *phil, int nphil, t_update update)
{
	pid_t		pid;
	pthread_t	death_checker;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		pthread_create(&death_checker, NULL, &check_die, &update);
		pthread_detach(death_checker);
		while (1)
			if (do_routine(&update, phil, nphil))
				return (1);
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
		create_process(phil, i, update[i]);
		i++;
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
