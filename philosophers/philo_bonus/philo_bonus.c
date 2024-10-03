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
                phil->die = 1;
                log_change(phil, nphil + 1, 5);
                return (NULL);
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
        if (update->total_eat == phil->num_eat || phil->die == 1)
        {
            return (NULL);
        }
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
        // check die or no return 0 or 1 , use the struct kinda to tell?
        if (phil->die == 1)
        {
            exit(1);
        }
        else
        {
            exit(0);
        }
    }
    else
    {
        phil->phil_pid[nphil] = pid;
    }
    return (0);
}

// -1 if sem_wait is fail & how to take care who take the fork
// if all eaten stop and how i know all eaten? i want stop pringting
// if something die i wanna stop
// using sem as death watcher is impossible 
// using sem as a eaten counter also impossible

void    wait_child(t_phil *phil)
{
    int i ;
    int exitcode;

    i = 0;
    while (i < phil->num_phil)
    {
        if (waitpid(phil->phil_pid[i], &phil->status[i], 0) > 0)
        {
            exitcode = phil->status[i] >> 8;

            if (exitcode == 1)
            {
                i = 0;
                while (i < phil->num_phil)
                {
                    kill(phil->phil_pid[i], SIGKILL);
                    i++;
                }
                return ;
            }
        }
        i++;
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

    //no need semaphone
    // created mutiple child
    // how to make sure if one child die then all child is die
    // you cant kill it inside the process because it doesnt have the kill pid right
    // if finish eat then return
    //  

    sem_close(phil.sem_take_fork);
    sem_close(phil.sem_fork);
    return (0);
}
