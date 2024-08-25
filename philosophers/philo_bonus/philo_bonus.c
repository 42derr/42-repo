#include "philo_bonus.h"

void    create_process(t_phil *phil, int nphil)
{
    pid_t pid;
    struct timeval tv;
    int eaten;
    
    eaten = 0;
    pid = fork();
    if (pid == -1)
        return ;
    if (pid == 0)
    {
        while (1)
        {
            sem_wait(phil->sem_take_fork);
            if (check_death(phil, nphil))
                return ;// kidna work but in some case still printing // what if die while eatingthis where you need thread bro fker
            //thread and ask them to do each activity
            sem_wait(phil->sem_fork);
            log_change(phil, nphil + 1, 1);
            sem_wait(phil->sem_fork);
            log_change(phil, nphil + 1, 1);
            sem_post(phil->sem_take_fork);
            log_change(phil, nphil + 1, 2);
            gettimeofday(&tv, NULL);
            phil->last_time[nphil] = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
            usleep(phil->time_eat * 1000);
            sem_post(phil->sem_fork);
            sem_post(phil->sem_fork);
            eaten++;
            if (eaten == phil->num_eat)
                exit(1);
            log_change(phil, nphil + 1, 3);
            usleep(phil->time_sleep * 1000);
            log_change(phil, nphil + 1, 4);
        }
    }
    else
    {
        phil->phil_pid[nphil] = pid;
    }
}

// -1 if sem_wait is fail & how to take care who take the fork
// if all eaten stop and how i know all eaten? i want stop pringting
// if something die i wanna stop
// using sem as death watcher is impossible 
// using sem as a eaten counter also impossible

void    wait_child(t_phil *phil, int diepid)
{
    int i ;

    i = 0;
    while (i < phil->num_phil)
    {
        waitpid(phil->phil_pid[i], NULL, 0);
        i++;
    }
    if (diepid)
        kill(diepid, SIGKILL);
    i = 0;
    while (i < phil->num_phil)
    {
        kill(phil->phil_pid[i], SIGKILL);
        i++;
    }
}

int main(int argc, char* argv[])
{
    t_phil phil;
    int i;

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
    phil.sem_die = sem_open(SEM_DIE, O_CREAT, 0660, 0);
    if (phil.sem_die == SEM_FAILED)
        return (printf("sem/philo_die"), 1);
    i = 0;
    while (i < phil.num_phil)
    {
        create_process(&phil, i);
        i++;
    }
    int diepid;
    diepid = fork();
    if (diepid == 0)
    {
        sem_wait(phil.sem_die);
        i = 0;
        while (i < phil.num_phil)
        {
            kill(phil.phil_pid[i], SIGKILL);
            i++;
        }
        wait_child(&phil, 0);
        exit(0);
    }
    else
    {
        wait_child(&phil, diepid);
    }
    sem_close(phil.sem_take_fork);
    sem_close(phil.sem_die);
    sem_close(phil.sem_fork);
    return (0);
}
