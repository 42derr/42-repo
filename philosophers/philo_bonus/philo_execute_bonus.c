#include "philo_bonus.h"

int    check_death(t_phil *phil, int nphil)
{
    struct timeval tv;
    long cur_time;

    gettimeofday(&tv, NULL);
    cur_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    if (((int)(cur_time - phil->last_time[nphil])) > phil->time_die)
    {
        log_change(phil, nphil + 1, 5);
        sem_post(phil->sem_die);
        return (1);
    }
    return (0);
}

// void    philo_eat(t_update *update, int firstfork, int secondfork)
// {
//     struct timeval tv;

//     if (update->phil->fork_state[firstfork] == 0
//         && update->phil->fork_state[secondfork] == 0
//         && !update->phil->die && should_eat(update))
//     {
//         update->phil->fork_state[firstfork] = 1;
//         log_change(update->phil, update->cur_phil + 1, 1);
//         update->phil->fork_state[secondfork] = 1;
//         log_change(update->phil, update->cur_phil + 1, 1);
//         log_change(update->phil, update->cur_phil + 1, 2);
//         gettimeofday(&tv, NULL);
//         update->last_eat = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
//         update->phil->last_time[update->cur_phil] = update->last_eat;
//         update->eating = 1;
//         update->total_eat++;
//     }
// }

// int    philo_think(t_update *update, int firstfork, int secondfork)
// {
//     if (update->eating == 1 && !update->phil->die)
//     {
//         usleep(update->phil->time_eat * 1000);
//         pthread_mutex_lock(&update->phil->lock);
//         update->phil->fork_state[firstfork] = 0;
//         update->phil->fork_state[secondfork] = 0;
//         pthread_mutex_unlock(&update->phil->lock);
//         if (update->total_eat == update->phil->num_eat)
//             return (1);
//         log_change(update->phil, update->cur_phil + 1, 3);
//         usleep(update->phil->time_sleep * 1000);
//         log_change(update->phil, update->cur_phil + 1, 4);
//         update->eating = 0;
//     }
//     return (0);
// }