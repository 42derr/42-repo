#include "philo.h"

void    log_change (t_phil *phil, int nphil, int cur)
{
    struct timeval tv;
    long cur_time;
    long timestamp;

    gettimeofday(&tv, NULL);
    cur_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    timestamp = cur_time - phil->start_time;
    if (cur == 1)
        printf("%ldms %d has taken a fork\n", timestamp, nphil);
    else if (cur == 2)
        printf("%ldms %d is eating\n", timestamp, nphil);
    else if (cur == 3)
        printf("%ldms %d is sleeping\n", timestamp, nphil);
    else if (cur == 4)
        printf("%ldms %d is thinking\n", timestamp, nphil);
    else if (cur == 5)
        printf("%ldms %d died\n", timestamp, nphil);
}

int   init_state(t_phil *phil)
{
    int i;

    phil->eat_state = (int *) malloc (sizeof(int) * phil->num_phil);
    if (!phil->eat_state)
        return (1);
    phil->fork_state = (int *) malloc (sizeof(int) * phil->num_phil);
    if (!phil->fork_state)
        return (1);
    phil->eat_accu = (int *) malloc (sizeof(int) * phil->num_phil);
    if (!phil->eat_accu)
        return (1);
    i = 0;
    while (i < phil->num_phil)
    {
        phil->eat_state[i] = 0;
        i++;
    }
    i = 0;
    while (i < phil->num_phil)
    {
        phil->fork_state[i] = 0;
        i++;
    }
    i = 0;
    while (i < phil->num_phil)
    {
        phil->eat_accu[i] = 0;
        i++;
    }
    return (0);
}

int    init_phil(t_phil *phil, char *argv[])
{
    int i;
    int j;
    struct timeval tv;

    i = 1;
    while (argv[i])
    {
        j = 0;
        while (argv[i][j])
        {
            if (!ft_strchr("0123456789", argv[i][j]))
                return (printf("There is a non number in args"), 1);
            j++;
        }
        i++;
    }
    phil->num_phil = ft_atoi(argv[1]);
    phil->time_die = ft_atoi(argv[2]);
    phil->time_eat =  ft_atoi(argv[3]);
    phil->time_sleep =  ft_atoi(argv[4]);
    phil->num_eat =  ft_atoi(argv[5]);
    gettimeofday(&tv, NULL);
    phil->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    phil->die = 0;
    if (init_state(phil))
        return (printf("malloc error on init_state"), 1);
    return (0);
}
