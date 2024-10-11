#include "philo.h"

void    handle_thread(t_phil *phil, t_update *update)
{
    int i;

    i = 0;
    while (i < phil->num_phil)
    {
        pthread_create(&phil->thread[i], NULL, &process_activity, &update[i]);
        i++;
    }
    i = 0;
    while (i < phil->num_phil)
    {
        pthread_join(phil->thread[i], NULL);
        i++;
    }
}

int main(int argc, char* argv[])
{
    t_phil phil;
    t_update *update;

    phil = (t_phil){0};
    pthread_mutex_init(&(phil.lock), NULL);
    if (argc < 5 || argc > 6)
        return (printf("./philo [number_of_philosophers] [time_to_die] [time_to_eat]"
            " [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n"), 1);
    if (init_phil(&phil, argc, argv))
        return (1);
    phil.thread = (pthread_t *) malloc (sizeof(pthread_t) * phil.num_phil);
    if (!phil.thread)
        return (error_handler("malloc error on thread",&phil,NULL), 1);
    update = init_update(&phil);
    if (!update)
        return (error_handler("malloc error on update",&phil, NULL), 1);
    handle_thread(&phil, update);
    pthread_mutex_destroy(&phil.lock);
    error_handler(NULL, &phil, update);
    return (0);
}
