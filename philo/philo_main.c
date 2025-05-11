#include "philosophers.h"

int main(int ac, char **av)
{
    t_data  data;

    if (ac < 5 || ac > 6)
    {
        printf("Usage: %s number_of_philosophers time_to_die ", av[0]);
        printf("time_to_eat time_to_sleep [number_of_meals]\n");
        return (1);
    }
    if (init_data(&data, ac, av))
        return (1);
    if (init_philos(&data))
    {
        cleanup(&data);
        return (1);
    }
    monitor(&data);
    cleanup(&data);
    return (0);
}
