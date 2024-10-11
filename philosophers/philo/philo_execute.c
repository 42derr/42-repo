#include "philo.h"

void    philo_eat(t_update *update, int firstfork, int secondfork)
{
    struct timeval tv;

    if (update->phil->fork_state[firstfork] == 0
        && update->phil->fork_state[secondfork] == 0
        && !update->phil->die && should_eat(update))
    {
        update->phil->fork_state[firstfork] = 1;
        log_change(update->phil, update->cur_phil + 1, 1);
        if (update->phil->num_phil == 1)
            return ;
        update->phil->fork_state[secondfork] = 1;
        log_change(update->phil, update->cur_phil + 1, 1);
        log_change(update->phil, update->cur_phil + 1, 2);
        gettimeofday(&tv, NULL);
        update->last_eat = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
        update->phil->last_time[update->cur_phil] = update->last_eat;
        update->eating = 1;
        update->total_eat++;
    }
}

int    philo_think(t_update *update, int firstfork, int secondfork)
{
    if (update->eating == 1)
    {
        usleep(update->phil->time_eat * 1000);
        pthread_mutex_lock(&update->phil->lock);
        if (update->phil->die)
        {
            pthread_mutex_unlock(&update->phil->lock);
            return (1);
        }
        update->phil->fork_state[firstfork] = 0;
        update->phil->fork_state[secondfork] = 0;
        pthread_mutex_unlock(&update->phil->lock);
        if (update->total_eat == update->phil->num_eat)
            return (1);
        log_change(update->phil, update->cur_phil + 1, 3);
        usleep(update->phil->time_sleep * 1000);
        log_change(update->phil, update->cur_phil + 1, 4);
        update->eating = 0;
    }
    return (0);
}

// bad delay

void    *process_activity(void *args)
{
    int firstfork;
    int secondfork;
    t_update *update;

    update = (t_update *) args;
    firstfork = update->cur_phil - 1;
    if (firstfork == -1)
        firstfork = update->phil->num_phil - 1;
    secondfork = update->cur_phil;
    while ((update->total_eat != update->phil->num_eat) || update->phil->num_eat == -1)
    {
        if (check_death(update))
            return (NULL);
        pthread_mutex_lock(&update->phil->lock);
        philo_eat(update, firstfork, secondfork);
        pthread_mutex_unlock(&update->phil->lock);
        if (philo_think(update, firstfork, secondfork))
            return (NULL);
    }
    return (NULL);
}

int    check_death(t_update *update)
{
    struct timeval tv;
    long cur_time;

    gettimeofday(&tv, NULL);
    cur_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    pthread_mutex_lock (&update->phil->lock);
    if (update->phil->die == 1)
    {
        pthread_mutex_unlock (&update->phil->lock);
        return (1);
    }
    if (((int)(cur_time - update->last_eat)) > update->phil->time_die)
    {
        log_change(update->phil, update->cur_phil + 1, 5);
        update->phil->die = 1;
        pthread_mutex_unlock (&update->phil->lock);
        return (1);
    }
    pthread_mutex_unlock (&update->phil->lock);
    return (0);
}