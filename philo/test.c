// void	philo_act(t_args *input)
// {
// 	int	i;

// 	input->simulation_off = false;
// 	input->philosophers = malloc(sizeof(t_philosopher) * input->philo_nbr);
// 	if (!input->philosophers)
// 		error_mes_exit("MALLOC ERROR\n");
// 	input->forks = malloc(sizeof(t_fork) * input->philo_nbr);
// 	if (!input->forks)
// 	{
// 		free(input->philosophers);
// 		error_mes_exit("MALLOC ERROR\n");
// 	}
// 	if (pthread_mutex_init(&input->print_mutex, NULL) != 0)
// 	{
// 		free(input->philosophers);
// 		free(input->forks);
// 		error_mes_exit("PRINT MUTEX INIT ERROR\n");
// 	}
// 	if (pthread_mutex_init(&input->status_mutex, NULL) != 0)
// 	{
// 		pthread_mutex_destroy(&input->print_mutex);
// 		free(input->philosophers);
// 		free(input->forks);
// 		error_mes_exit("STATUS MUTEX INIT ERROR\n");
// 	}
// 	init_forks(input);
// 	init_philosophers(input);
// 	input->start_time = get_current_time();
// 	create_threads(input);
// 	monitor_philosophers(input);
// 	for (i = 0; i < input->philo_nbr; i++)
// 	{
// 		pthread_join(input->philosophers[i].thread_id, NULL);
// 	}
// 	cleanup_resources(input);
// }

// # include "philosophers.h"
#include <stdlib.h>
#include <pthread.h>
// #include "philo.h" // Assuming necessary headers are included here


void	monitor_philosophers(t_args *input)
{
	int		i;
	int		full_philos;
	long	now;
	long	time_since_meal;

	while (1)
	{
		full_philos = 0;
		i = 0;
		while (i < input->philo_nbr)
		{
			pthread_mutex_lock(&input->status_mutex);
			if (input->meals_limit > 0 && input->philosophers[i].meal_count >= input->meals_limit)
				full_philos++;
			now = get_current_time();
			time_since_meal = now - input->philosophers[i].last_meal_time;
			if (!input->simulation_off && time_since_meal > input->time_to_die)
			{
				input->simulation_off = true;
				pthread_mutex_unlock(&input->status_mutex);
				pthread_mutex_lock(&input->print_mutex);
				printf("%ld %d %s\n", now - input->start_time, input->philosophers[i].philo_id, "died");
				pthread_mutex_unlock(&input->print_mutex);
				return ;
			}
			pthread_mutex_unlock(&input->status_mutex);
			i++;
		}
		pthread_mutex_lock(&input->status_mutex);
		if (input->meals_limit > 0 && full_philos == input->philo_nbr)
		{
			input->simulation_off = true;
			pthread_mutex_unlock(&input->status_mutex);
			return ;
		}
		pthread_mutex_unlock(&input->status_mutex);
		usleep(1000);
	}
}









// Check if a philosopher has died
static int	check_philosopher_death(t_args *input, int i)
{
    long	now;
    long	time_since_meal;

    pthread_mutex_lock(&input->status_mutex);
    now = get_current_time();
    time_since_meal = now - input->philosophers[i].last_meal_time;
    if (!input->simulation_off && time_since_meal > input->time_to_die)
    {
        input->simulation_off = true;
        pthread_mutex_unlock(&input->status_mutex);
        pthread_mutex_lock(&input->print_mutex);
        printf("%ld %d %s\n", now - input->start_time,
            input->philosophers[i].philo_id, "died");
        pthread_mutex_unlock(&input->print_mutex);
        return (1);
    }
    pthread_mutex_unlock(&input->status_mutex);
    return (0);
}

// Check if all philosophers are full
static int	check_all_philosophers_full(t_args *input)
{
    int	i;
    int	full_philos;

    full_philos = 0;
    i = 0;
    while (i < input->philo_nbr)
    {
        pthread_mutex_lock(&input->status_mutex);
        if (input->meals_limit > 0 &&
            input->philosophers[i].meal_count >= input->meals_limit)
            full_philos++;
        pthread_mutex_unlock(&input->status_mutex);
        i++;
    }
    return (full_philos == input->philo_nbr);
}


void	monitor_philosophers(t_args *input)
{
    int	i;

    while (1)
    {
        i = 0;
        while (i < input->philo_nbr)
        {
            if (check_philosopher_death(input, i))
                return;
            i++;
        }

        pthread_mutex_lock(&input->status_mutex);
        if (input->meals_limit > 0 && check_all_philosophers_full(input))
        {
            input->simulation_off = true;
            pthread_mutex_unlock(&input->status_mutex);
            return;
        }
        pthread_mutex_unlock(&input->status_mutex);
        usleep(1000);
    }
}
