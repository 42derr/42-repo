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
            sem_wait(phil->take_fork);
            sem_wait(phil->fork); // another sem for knowing if someone taking the fork
            // check for death before taking a fork
            log_change(phil, nphil + 1, 1);
            sem_wait(phil->fork);
            log_change(phil, nphil + 1, 1);
            sem_post(phil->take_fork);
            log_change(phil, nphil + 1, 2);
            gettimeofday(&tv, NULL);
            phil->last_time[nphil] = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
            check_death(phil, nphil);
            usleep(phil->time_eat * 1000);
            sem_post(phil->fork);
            sem_post(phil->fork);
            log_change(phil, nphil + 1, 3);
            usleep(phil->time_sleep * 1000);
            log_change(phil, nphil + 1, 4);
            eaten++;
            if (eaten == phil->num_eat)
                exit(1);
        }
    }
    else
    {
        phil->phil_pid[nphil] = pid;
    }
}
//prossess that track child die?
void    wait_child(t_phil *phil)
{
        printf("OK ----\n");
        waitpid(phil->phil_pid[4], NULL, 0);
        kill(phil->phil_pid[0], SIGKILL);
        kill(phil->phil_pid[1], SIGKILL);
        kill(phil->phil_pid[2], SIGKILL);
        kill(phil->phil_pid[3], SIGKILL);
        kill(phil->phil_pid[4], SIGKILL);
        printf("OK ----\n");
}
// check die, update to semaphore;
// save all on pid_t if someone c you die? wtf  kill(pid, SIGKILL);
// -1 if sem_wait is fail

int main(int argc, char* argv[])
{
    t_phil phil;
    t_update *update;
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
        return (printf("Philosophers can't eat! there only 1 fork\n"), 1);// use thread like mandatory or it will not work
    phil.fork = sem_open(SEM_FORK, O_CREAT, 0660, phil.num_phil);
    if (phil.fork == SEM_FAILED)
        return (printf("sem/philo_fork"), 1);
    phil.take_fork = sem_open(SEM_TAKE_FORK, O_CREAT, 0660, 1);
    if (phil.take_fork == SEM_FAILED)
        return (printf("sem/philo_take_fork"), 1);
    phil.sem_die = sem_open(SEM_DIE, O_CREAT, 0660, 1);
    if (phil.sem_die == SEM_FAILED)
        return (printf("sem/philo_die"), 1);
    i = 0;
    while (i < phil.num_phil)
    {
        create_process(&phil, i);
        i++;
    }
    wait_child(&phil);
    printf("GG --------------------------------------------------------------------------\n");
    sem_close(phil.fork);
    return (0);
}
