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

typedef struct s_phil
{
    sem_t *sem_take_fork;
    sem_t *sem_fork;
    sem_t *sem_die;
    pid_t *phil_pid;
    long *last_time;
    long start_time;
    int num_phil;
    int time_die;
    int time_eat;
    int time_sleep;
    int num_eat;
    int die;
    int eaten;
    int done;
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

int   init_phil_helper(t_phil *phil);
int    init_phil(t_phil *phil, char *argv[]);
t_update *init_update(t_phil *phil);

int    check_death(t_phil *phil, int nphil);
void    *process_activity(void *args);


# endif