#include "philo.h"

int init_thread(t_phil *phil)
{
    phil->thread = (pthread_t **) malloc (sizeof(pthread_t) * phil->num_phil);
    if (!phil->thread)
        return (NULL);
}

int main(int argc, char* argv[])
{
    t_phil phil;

    if (argc != 6)
        return (printf("./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n"), 1);
    if (init_phil(&phil, argv))
        return (printf("There is a non number in args"), 1);
    if (!init_thread)
        return (printf("Error in init_thread"), 1);
}
