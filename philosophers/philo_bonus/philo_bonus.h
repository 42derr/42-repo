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

# define SEM_FORK "/philo_fork"
# define SEM_TAKE_FORK "/philo_takefork"
# define SEM_DIE "/philo_die"

typedef struct s_phil
{
    sem_t *take_fork;
    sem_t *fork;
    sem_t *sem_die;
    pid_t *phil_pid;
    long *last_time;
    long start_time;
    int num_phil;
    int time_die;
    int time_eat;
    int time_sleep;
    int num_eat;
} t_phil ;

typedef struct s_update
{
    t_phil *phil;
    int cur_phil;
    int total_eat;
    int eating;
    long last_eat;
} t_update ;

char	*ft_strchr(const char *s, int c);
int	ft_atoi(const char *nptr);

void    log_change (t_phil *phil, int nphil, int cur);
int    should_eat(t_update *update);
t_update *init_update(t_phil *phil);
int   init_phil_helper(t_phil *phil);
int    init_phil(t_phil *phil, char *argv[]);

int    check_death(t_phil *phil, int nphil);
void    philo_eat(t_update *update, int firstfork, int secondfork);
int    philo_think(t_update *update, int firstfork, int secondfork);
void    *process_activity(void *args);

void    handle_thread(t_phil *phil, t_update *update);

# endif