#include "philosophers.h"

static int init_mutexes(t_data *data)
{
    int i;

    if (pthread_mutex_init(&data->print_mutex, NULL))
        return (1);
    if (pthread_mutex_init(&data->death_mutex, NULL))
    {
        pthread_mutex_destroy(&data->print_mutex);
        return (1);
    }
    if (pthread_mutex_init(&data->full_mutex, NULL))
    {
        pthread_mutex_destroy(&data->print_mutex);
        pthread_mutex_destroy(&data->death_mutex);
        return (1);
    }
    i = -1;
    while (++i < data->philo_count)
    {
        if (pthread_mutex_init(&data->forks[i].mutex, NULL))
        {
            while (--i >= 0)
                pthread_mutex_destroy(&data->forks[i].mutex);
            return (1);
        }
        data->forks[i].id = i;
    }
    return (0);
}

int init_data(t_data *data, int ac, char **av)
{
    data->philo_count = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->meal_limit = (ac == 6) ? ft_atoi(av[5]) : -1;
    data->sim_stop = false;
    data->start_time = get_time();

    if (data->philo_count <= 0 || data->time_to_die <= 0 ||
        data->time_to_eat <= 0 || data->time_to_sleep <= 0 ||
        (ac == 6 && data->meal_limit <= 0))
        return (1);

    data->philos = malloc(sizeof(t_philo) * data->philo_count);
    data->forks = malloc(sizeof(t_fork) * data->philo_count);
    if (!data->philos || !data->forks)
        return (1);

    if (init_mutexes(data))
    {
        free(data->philos);
        free(data->forks);
        return (1);
    }
    return (0);
}
