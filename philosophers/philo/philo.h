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
    pthread_t *thread;
    pthread_mutex_t lock;
    int *fork_state;
    int *eat_state;
    int *eat_accu;
    long start_time;
    int num_phil;
    int time_die;
    int time_eat;
    int time_sleep;
    int num_eat;
    int die;
} t_phil ;

typedef struct s_update
{
    t_phil *phil;
    int cur_phil;
    int total_eat;
    int eating;
    int last_eat;
} t_update ;

char	*ft_strchr(const char *s, int c);
int	ft_atoi(const char *nptr);

void    log_change (t_phil *phil, int nphil, int cur);
int    init_phil(t_phil *phil, char *argv[]);
int    check_death(t_update *update);
int should_eat(t_update *update);

#endif