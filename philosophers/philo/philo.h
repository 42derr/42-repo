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
    pthread_t **thread;
    int num_phil;
    int time_die;
    int time_eat;
    int time_sleep;
    int num_eat;
} t_phil ;

char	*ft_strchr(const char *s, int c);
int	ft_atoi(const char *nptr);

void    log_change (long time, int phil, int cur);
int    init_phil(t_phil *phil, char *argv[]);

#endif