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

int    should_eat(t_update *update)
{
    int i;
    long min;

    i = 0;
    if (update->total_eat == 0)
        return (1);
    min =  update->phil->last_time[update->cur_phil];
    while (i < update->phil->num_phil)
    {
        if (min > update->phil->last_time[i])
            return (0);
        i++;
    }
    return (1);
}

t_update *init_update(t_phil *phil)
{
    t_update *update;
    int i;

    i = 0;
    update = (t_update *) malloc (sizeof(t_update) * phil->num_phil);
    if (!update)
        return (NULL);
    while (i < phil->num_phil)
    {
        update[i].phil = phil;
        update[i].cur_phil = i;
        update[i].eating = 0;
        update[i].last_eat = phil->start_time;
        update[i].total_eat = 0;
        i++;
    }
    return (update);
}

int   init_phil_helper(t_phil *phil)
{
    int i;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    phil->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    phil->fork_state = (int *) malloc (sizeof(int) * phil->num_phil);
    if (!phil->fork_state)
        return(error_handler("malloc error on phil->fork_state", NULL, NULL), 1);
    i = 0;
    while (i < phil->num_phil)
    {
        phil->fork_state[i] = 0;
        i++;
    }
    phil->last_time = (long *) malloc (sizeof(long) * phil->num_phil);
    if (!phil->last_time)
       return (error_handler("malloc error on phil->last_time", phil, NULL), 1);
    i = 0;
    while (i < phil->num_phil)
    {
        phil->last_time[i] = 0;
        i++;
    }
    return (0);
}

int    init_phil(t_phil *phil, char *argv[])
{
    int i;
    int j;

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
    phil->die = 0;
    if (init_phil_helper(phil))
        return (1);
    return (0);
}
