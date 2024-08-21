#include "philo.h"

void    log_change (long time, int phil, int cur)
{
    if (cur == 1)
        printf("%ld %d has taken a fork\n", time, phil);
    else if (cur == 2)
        printf("%ld %d is eating\n", time, phil);
    else if (cur == 3)
        printf("%ld %d is sleeping\n", time, phil);
    else if (cur == 4)
        printf("%ld %d is thinking\n", time, phil);
    else if (cur == 5)
        printf("%ld %d died\n", time, phil);
}

int    init_phil(t_phil *phil, char *argv[])
{
    int i;
    int j;

    i = 1;
    while (argv[i])
    {
        j = 0;
        while (argv[i][j])
        {
            if (!ft_strchr("0123456789", argv[i][j]))
                return (1);
            j++;
        }
        i++;
    }
    phil->num_phil = ft_atoi(argv[1]);
    phil->time_die = ft_atoi(argv[2]);
    phil->time_eat =  ft_atoi(argv[3]);
    phil->time_sleep =  ft_atoi(argv[4]);
    phil->num_eat =  ft_atoi(argv[5]);
    return (0);
}
