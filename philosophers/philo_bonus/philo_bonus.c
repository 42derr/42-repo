#include "philo_bonus.h"

void    *check_die(void *args)
{
    struct timeval tv;
    long cur;
    long start;
    t_update *update;
    t_phil *phil;
    int nphil;

    update = (t_update *)args;
    phil = update->phil;
    nphil = update->cur_phil;
    start = phil->start_time;
    while (1)
    {
        gettimeofday(&tv, NULL);
        cur = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
        if (cur - start >= phil->time_die)
        {
            if (update->total_eat == update->phil->num_eat)
            {
                break;
            }
            if (phil->eaten == 0)
            {
                sem_wait(phil->sem_die);
                log_change(phil, nphil + 1, 5);
                exit (1);
            }
            else
                phil->eaten = 0;
            start = cur;
        }
    }
    return (NULL);
}

void    *do_routine(void *args)
{
    int eaten;
    t_update *update;
    t_phil *phil;
    int nphil;

    update = (t_update *)args;
    phil = update->phil;
    nphil = update->cur_phil;
    eaten = 0;
    while (1)
    {
        sem_wait(phil->sem_take_fork);
        sem_wait(phil->sem_fork);
        log_change(phil, nphil + 1, 1);
        sem_wait(phil->sem_fork);
        log_change(phil, nphil + 1, 1);
        sem_post(phil->sem_take_fork);
        log_change(phil, nphil + 1, 2);
        usleep(phil->time_eat * 1000);
        sem_post(phil->sem_fork);
        sem_post(phil->sem_fork);
        phil->eaten = 1;
        update->total_eat++;
        if (update->total_eat == phil->num_eat)
            exit (0);
        log_change(phil, nphil + 1, 3);
        usleep(phil->time_sleep * 1000);
        log_change(phil, nphil + 1, 4);
    }
    return (NULL);
}

int    create_process(t_phil *phil, int nphil, t_update update)
{
    pid_t pid;
    struct timeval tv;
    int eaten;
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    
    eaten = 0;
    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {
        pthread_create(&thread1, NULL, &check_die, &update);
        pthread_create(&thread2, NULL, &do_routine, &update);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
    }
    else
    {
        phil->phil_pid[nphil] = pid;
    }
    return (0);
}

void    wait_child(t_phil *phil)
{
    int i;
    int exitcode;
    int status;

    if (waitpid(-1, &status, 0) > 0)
    {
        exitcode = status >> 8;
        if (exitcode != 1)
        {
            wait_child (phil);
            return ;
        }
        i = 0;
        while (i < phil->num_phil)
        {
            kill(phil->phil_pid[i], SIGKILL);
            i++;
        }
        return ;
    }
}

int main(int argc, char* argv[])
{
    t_phil phil;
    int i;
    t_update *update;

    if (argc != 6)
        return (printf("./philo [number_of_philosophers] [time_to_die] [time_to_eat]"
            " [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n"), 1);
    sem_unlink(SEM_FORK);
    sem_unlink(SEM_TAKE_FORK);
    sem_unlink(SEM_DIE);
    if (init_phil(&phil, argv))
        return (1);
    if (phil.num_phil == 1)
        return (printf("Philosophers can't eat! there only 1 fork\n"), 1);
    phil.sem_fork = sem_open(SEM_FORK, O_CREAT, 0660, phil.num_phil);
    if (phil.sem_fork == SEM_FAILED)
        return (printf("sem/philo_fork"), 1);
    phil.sem_take_fork = sem_open(SEM_TAKE_FORK, O_CREAT, 0660, 1);
    if (phil.sem_take_fork == SEM_FAILED)
        return (printf("sem/philo_take_fork"), 1);
    phil.sem_die = sem_open(SEM_DIE, O_CREAT, 0660, 1);
    update = init_update(&phil);
    if (!update)
        return (1);
    i = 0;
    while (i < phil.num_phil)
    {
        create_process(&phil, i, update[i]);
        i++;
    }
    wait_child(&phil);
    sem_close(phil.sem_take_fork);
    sem_close(phil.sem_fork);
    sem_close(phil.sem_die);
    return (0);
}
