#include "philo.h"

void    *process_activity(void *args)
{
    int firstfork;
    int secondfork;
    t_update *update;
    struct timeval tv;

    update = (t_update *) args;
    firstfork = update->cur_phil - 1;
    if (firstfork == -1)
        firstfork = update->phil->num_phil - 1;
    secondfork = update->cur_phil;
    //let the one with least total_eat eat
    while (!update->phil->die && update->total_eat != update->phil->num_eat)
    {
        check_death(update);
        pthread_mutex_lock(&update->phil->lock);
        if (update->phil->fork_state[firstfork] == 0 && update->phil->fork_state[secondfork] == 0
                && update->phil->eat_state[update->cur_phil] == 0)
        {
            update->phil->fork_state[firstfork] = 1;
            log_change(update->phil, update->cur_phil + 1, 1);
            update->phil->fork_state[secondfork] = 1;
            log_change(update->phil, update->cur_phil + 1, 1);
            update->phil->eat_state[update->cur_phil] = 1;
            log_change(update->phil, update->cur_phil + 1, 2);
            gettimeofday(&tv, NULL);
            update->last_eat = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
            update->eating = 1;
            update->total_eat++;
            update->phil->eat_accu[update->cur_phil]++;
        }
        pthread_mutex_unlock(&update->phil->lock);
        if (update->eating == 1 && !update->phil->die)
        {
            usleep(update->phil->time_eat * 1000);
            pthread_mutex_lock(&update->phil->lock);
            update->phil->fork_state[firstfork] = 0;
            update->phil->fork_state[secondfork] = 0;
            update->phil->eat_state[update->cur_phil] = 0;
            pthread_mutex_unlock(&update->phil->lock);
            log_change(update->phil, update->cur_phil + 1, 3);
            usleep(update->phil->time_sleep * 1000);
            log_change(update->phil, update->cur_phil + 1, 4);
            update->eating = 0;
        }
    }
    return (NULL);
    //20 % fail when it not urutan
}

int should_eat(t_update *update)
{
    int i;
    int max;
    int yes;

    yes = 0;
    i = 0;
    max = update->phil->eat_accu[0];
    while (i < update->cur_phil)
    {
        if (max < update->phil->eat_accu[i])
            max = update->phil->eat_accu[i];
        i++;
    }
    i = 0;
    while (i < update->cur_phil)
    {
        if (max > update->phil->eat_accu[i])
            yes = 1;
        i++;
    }
    if (yes && update->phil->eat_accu[update->cur_phil] == max)
        return (0);
    return (1);
}

int    check_death(t_update *update)
{
    struct timeval tv;
    long cur_time;

    gettimeofday(&tv, NULL);
    cur_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    if (((int)(cur_time - update->last_eat)) > update->phil->time_die)
    {
        log_change(update->phil, update->cur_phil + 1, 5);
        update->phil->die = 1;
        return (1);
    }
    return (0);
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

int main(int argc, char* argv[])
{
    t_phil phil;
    t_update *update;
    int j;


    pthread_mutex_init(&(phil.lock), NULL);
    if (argc != 6)
        return (printf("./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n"), 1);
    if (init_phil(&phil, argv))
        return (1);
    if (phil.num_phil == 1)
        return (printf("Philosophers can't eat! there only 1 fork\n"), 1); 
    phil.thread = (pthread_t *) malloc (sizeof(pthread_t) * phil.num_phil);
    if (!phil.thread)
        return (printf("Error in init_thread\n"), 1);
    update = init_update(&phil);
    j = 0;
    while (j < phil.num_phil)
    {
        pthread_create(&phil.thread[j], NULL, &process_activity, &update[j]);
        j++;
    }
    j = 0;
    while (j < phil.num_phil)
    {
        pthread_join(phil.thread[j], NULL);
        j++;
    }
    pthread_mutex_destroy(&phil.lock);
    return (0);
}
