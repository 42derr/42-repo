/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 01:34:19 by dfasius           #+#    #+#             */
/*   Updated: 2024/10/16 01:43:22 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h> 
# include <unistd.h>

typedef struct s_phil
{
	pthread_t		*thread;
	int				*fork_state;
	long			*last_time;
	pthread_mutex_t	lock;
	long			start_time;
	int				num_phil;
	int				finish;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	int				die;
}	t_phil;

typedef struct s_update
{
	t_phil	*phil;
	int		cur_phil;
	int		total_eat;
	int		eating;
	long	last_eat;
}	t_update;

void		handle_detach(t_phil *phil, int j);
int			handle_thread(t_phil *phil, t_update *update);

void		log_change(t_phil *phil, int nphil, int cur);
int			should_eat(t_update *update);
t_update	*init_update(t_phil *phil);
int			init_phil_helper(t_phil *phil);
int			init_phil(t_phil *phil, int argc, char **argv);

char		*ft_strchr(const char *s, int c);
int			ft_atoi(const char *nptr);
void		error_handler(char *buffer, t_phil *phil, t_update *update);
int			check_non_number(char **argv);

int			philo_eat(t_update *update, int firstfork, int secondfork);
int			philo_think(t_update *update, int firstfork, int secondfork);
void		*process_activity(void *args);
int			check_death_helper(t_update *update, int i);
void		*check_death(void *args);

#endif
