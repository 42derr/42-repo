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