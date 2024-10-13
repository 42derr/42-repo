#include "philo.h"

void    philo_eat(t_update *update, int firstfork, int secondfork)
{
    struct timeval tv;

    pthread_mutex_lock(&update->phil->lock);
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
    pthread_mutex_unlock(&update->phil->lock);
}

int    philo_think(t_update *update, int firstfork, int secondfork)
{
    if (update->eating == 1)
    {
        usleep(update->phil->time_eat * 1000);
        pthread_mutex_lock(&update->phil->lock);
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
// philo late to die because when they think -> one monitoring thread
// philo after eat just exit do not do think or sleep :)

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
        philo_eat(update, firstfork, secondfork);
        if (philo_think(update, firstfork, secondfork))
            return (NULL);
    }
    return (NULL);
}

void    *check_death(void *args)
{
    struct timeval tv;
    long cur_time;
    t_update *update;
    int i;

    i = 0;
    update = (t_update *) args;
    while (1)
    {
        i = 0;
        while (i < update[0].phil->num_phil)
        {
            gettimeofday(&tv, NULL);
            cur_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
            if (cur_time == 0)
                return(NULL);
            pthread_mutex_lock (&update[0].phil->lock);
            if (((int)(cur_time - update[i].last_eat)) > update[0].phil->time_die)
            {
                log_change(update[i].phil, update[i].cur_phil + 1, 5);
                update[0].phil->die = 1;
                pthread_mutex_unlock (&update[0].phil->lock);
                exit(0);
                return (NULL);
            }
            pthread_mutex_unlock (&update[0].phil->lock);
            i++;
        }
    }
    return (NULL);
}