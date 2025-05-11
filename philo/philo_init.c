#include "philosophers.h"

int init_mutexes(t_data *data)
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

int init_phil_mutexes(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_count)
    {
        if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL))
        {
            while (--i >= 0)
            {
                pthread_mutex_destroy(&data->philos[i].meal_mutex);
                pthread_mutex_destroy(&data->philos[i].last_meal_mutex);
            }
            return (1);
        }
        if (pthread_mutex_init(&data->philos[i].last_meal_mutex, NULL))
        {
            pthread_mutex_destroy(&data->philos[i].meal_mutex);
            while (--i >= 0)
            {
                pthread_mutex_destroy(&data->philos[i].meal_mutex);
                pthread_mutex_destroy(&data->philos[i].last_meal_mutex);
            }
            return (1);
        }
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

int init_philos(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_count)
    {
        data->philos[i].id = i + 1;
        data->philos[i].data = data;
        data->philos[i].meal_count = 0;
        data->philos[i].full = false;
        data->philos[i].last_meal = get_time();
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
    }

    if (init_phil_mutexes(data))
        return (1);

    i = -1;
    while (++i < data->philo_count)
    {
        if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]))
        {
            pthread_mutex_lock(&data->death_mutex);
            data->sim_stop = true;
            pthread_mutex_unlock(&data->death_mutex);
            i--;
            while (i >= 0)
                pthread_join(data->philos[i--].thread, NULL);
            return (1);
        }
    }
    return (0);
}
