/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:46:53 by dfasius           #+#    #+#             */
/*   Updated: 2024/10/21 19:49:39 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

# define SEM_FORK "fork"
# define SEM_TAKE_FORK "take_fork"
# define SEM_DIE "die"
# define SEM_CHECK "check"

typedef struct s_phil
{
	sem_t	*sem_take_fork;
	sem_t	*sem_fork;
	sem_t	*sem_die;
	sem_t	*sem_check;
	pid_t	*phil_pid;
	long	start_time;
	int		num_phil;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		num_eat;
	int		eaten;
}	t_phil;

typedef struct s_update
{
	t_phil	*phil;
	int		cur_phil;
	int		total_eat;
}	t_update;

int			create_process(t_phil *phil, int nphil, t_update update);
void		create_child(t_phil *phil, t_update *update);

char		*ft_strchr(const char *s, int c);
int			ft_atoi(const char *nptr);
int			check_non_number(char **argv);
void		error_handler(char *buffer, t_phil *phil, t_update *update);
long		ft_time(void);

void		*check_die(void *args);
void		wait_child(t_phil *phil);
int			do_routine(t_update *update, t_phil *phil, int nphil);

void		log_change(t_phil *phil, int nphil, int cur);
int			init_phil_helper(t_phil *phil);
int			init_phil(t_phil *phil, int argc, char *argv[]);
t_update	*init_update(t_phil *phil);
int			init_sem(t_phil *phil);

#endif
