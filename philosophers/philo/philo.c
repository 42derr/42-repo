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
    int j;

    pthread_mutex_init(&(phil.lock), NULL);
    if (argc != 6)
        return (printf("./philo [number_of_philosophers] [time_to_die] [time_to_eat]"
            " [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n"), 1);
    if (init_phil(&phil, argv))
        return (1);
    if (phil.num_phil == 1)
        return (printf("Philosophers can't eat! there only 1 fork\n"), 1); 
    phil.thread = (pthread_t *) malloc (sizeof(pthread_t) * phil.num_phil);
    if (!phil.thread)
        return (printf("Error in init_thread\n"), 1);
    update = init_update(&phil);
    handle_thread(&phil, update);
    pthread_mutex_destroy(&phil.lock);
    return (0);
}
