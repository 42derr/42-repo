/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 00:46:20 by dfasius           #+#    #+#             */
/*   Updated: 2024/10/16 00:52:14 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_detach(t_phil *phil, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		pthread_detach(phil->thread[i]);
		i++;
	}
}

int	handle_thread(t_phil *phil, t_update *update)
{
	int			i;
	pthread_t	death_checker;

	i = 0;
	while (i < phil->num_phil)
	{
		if (pthread_create(&phil->thread[i], NULL,
				&process_activity, &update[i]) != 0)
			return (handle_detach(phil, i), 1);
		i++;
	}
	if (pthread_create(&death_checker, NULL, &check_death, update) != 0)
		return (handle_detach(phil, phil->num_phil + 1), 1);
	i = 0;
	while (i < phil->num_phil)
	{
		pthread_join(phil->thread[i], NULL);
		i++;
	}
	pthread_join(death_checker, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_phil		phil;
	t_update	*update;

	if (argc < 5 || argc > 6)
		return (printf("./philo [number_of_philosophers] [time_to_die]"
				" [time_to_eat] [time_to_sleep] "
				"[number_of_times_each_philosopher_must_eat]\n"), 1);
	phil = (t_phil){0};
	if (pthread_mutex_init(&(phil.lock), NULL) == -1)
		return (printf("Failed to initialize mutex"), 1);
	if (init_phil(&phil, argc, argv))
		return (1);
	phil.thread = (pthread_t *) malloc (sizeof(pthread_t) * phil.num_phil);
	if (!phil.thread)
		return (error_handler("malloc error on thread", &phil, NULL), 1);
	update = init_update(&phil);
	if (!update)
		return (error_handler("malloc error on update", &phil, NULL), 1);
	handle_thread(&phil, update);
	pthread_mutex_destroy(&phil.lock);
	error_handler(NULL, &phil, update);
	return (0);
}
