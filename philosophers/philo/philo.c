#include "philo.h"

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
        update->eat = 1;
    }
    pthread_mutex_unlock(&update->phil->lock);
    if (update->eat == 1)
    {
        usleep(update->phil->time_eat * 1000);
        log_change(update->phil, update->cur_phil + 1, 3); //sleep //make sleep state & update
        usleep(update->phil->time_sleep * 1000); //sleep
        log_change(update->phil, update->cur_phil + 1, 4); //think
    }
    //problem is they wait for the sleep...
    update->eat = 0;
    return (NULL);
}
//process do everything until one die while no one die
//join all of them later

int    check_eat(t_phil *phil)
{
    int i;

    i = 0;
    while (i < phil->num_phil)
    {
        if (phil->eat_state[i] == 0)
            return (1);
        i++;
    }
    return (0);
}

void    reset_check_eat(t_phil *phil)
{
    int i;

    i = 0;
    while (i < phil->num_phil)
    {
        phil->eat_state[i] = 0;
        i++;
    }
}

void    reset_fork_state(t_phil *phil)
{
    int i;

    i = 0;
    while (i < phil->num_phil)
    {
        phil->fork_state[i] = 0;
        i++;
    }
}

int    check_death(t_phil *phil)
{
    int i;
    struct timeval tv;
    long cur_time;

    gettimeofday(&tv, NULL);
    cur_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    if (((int)(cur_time - phil->last_eat)) > phil->time_die)
    {
        i = 0;
        while (i < phil->num_phil)
        {
            if (phil->eat_state[i] == 0)
                log_change(phil, i + 1, 5);
            i++;
        }
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
    // printf("%d -------\n", phil->num_phil);
    if (!update)
        return (NULL);
    while (i < phil->num_phil)
    {
        update[i].phil = phil;
        update[i].cur_phil = i;
        update[i].eat = 0;
        i++;
    }
    return (update);
}

int main(int argc, char* argv[])
{
    t_phil phil;
    t_update *update;
    struct timeval tv;
    int i;
    int j;

    pthread_mutex_init(&(phil.lock), NULL);
    if (argc != 6)
        return (printf("./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n"), 1);
    if (init_phil(&phil, argv))
        return (1);
    if (phil.num_phil == 1)
        return (printf("Philosophers can't eat! there only 1 fork"), 1); 
    phil.thread = (pthread_t *) malloc (sizeof(pthread_t) * phil.num_phil);
    if (!phil.thread)
        return (printf("Error in init_thread"), 1);
    update = init_update(&phil);
    i = 0;
    while (i < phil.num_eat)
    {
        while (check_eat(&phil))
        {
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
            reset_fork_state(&phil);
            if (phil.last_eat == 0)
                phil.last_eat = phil.start_time;
            if (check_death(&phil))
                return (1);
        }
        gettimeofday(&tv, NULL);
        phil.last_eat = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        reset_check_eat(&phil);
        i++;
    }
    pthread_mutex_destroy(&phil.lock);
    return (0);
}
