/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:50:51 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/11 09:54:11 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_forks(t_args *input)
{
	int	x;

	x = 0;
	while (x < input->philo_nbr)
	{
		if (pthread_mutex_init(&(input->forks[x].fork_mutex), NULL) != 0)
		{
			while (--x >= 0)
				pthread_mutex_destroy(&(input->forks[x].fork_mutex));
			free(input->forks);
			free(input->philosophers);
			error_mes_exit("MUTEX INIT. ERROR\n");
		}
		input->forks[x].fork_id = x;
		x++;
	}
}

void	init_philosophers(t_args *input)
{
	int	x;

	x = 0;
	while (x < input->philo_nbr)
	{
		input->philosophers[x].philo_id = x + 1;
		input->philosophers[x].meal_count = 0;
		input->philosophers[x].full = 0;
		input->philosophers[x].last_meal_time = get_current_time();
		input->philosophers[x].right_fork = &input->forks[x];
		input->philosophers[x].left_fork = &input->forks[(x + 1) % input->philo_nbr];
		input->philosophers[x].input = input;
		x++;
	}
}

void	create_threads(t_args *input)
{
	int	i;

	i = 0;
	while (i < input->philo_nbr)
	{
		if (pthread_create(&(input->philosophers[i].thread_id), NULL, philosopher_routine, &(input->philosophers[i])) != 0)
		{
			input->simulation_off = true;
			i--; // Go back one to start joining created threads
			while (i >= 0)
			{
				pthread_join(input->philosophers[i].thread_id, NULL);
				i--;
			}
			error_mes_exit("THREAD CREATION ERROR\n");
		}
		i++;
	}
}


// void	philo_act(t_args *input)
// {
//     int	i;

//     init_resources(input);
//     init_mutexes(input);
//     start_simulation(input);
//     i = 0;
//     while (i < input->philo_nbr)
//         pthread_join(input->philosophers[i++].thread_id, NULL);
//     cleanup_resources(input);
// }
//////////////////////////////////////////
////////////////////////////////////

int	init_memory(t_args *input)
{
    input->philosophers = malloc(sizeof(t_philosopher) * input->philo_nbr);
    if (!input->philosophers)
    {
        error_mes_exit("MALLOC ERROR\n");
        return (1);
    }

    input->forks = malloc(sizeof(t_fork) * input->philo_nbr);
    if (!input->forks)
    {
        free(input->philosophers);
        error_mes_exit("MALLOC ERROR\n");
        return (1);
    }
    return (0);
}

int	init_mutexes(t_args *input)
{
    if (pthread_mutex_init(&input->print_mutex, NULL) != 0)
    {
        free(input->philosophers);
        free(input->forks);
        error_mes_exit("PRINT MUTEX INIT ERROR\n");
        return (1);
    }

    if (pthread_mutex_init(&input->status_mutex, NULL) != 0)
    {
        pthread_mutex_destroy(&input->print_mutex);
        free(input->philosophers);
        free(input->forks);
        error_mes_exit("STATUS MUTEX INIT ERROR\n");
        return (1);
    }
    return (0);
}

void	free_memory(t_args *input)
{
    free(input->philosophers);
    free(input->forks);
}



////
void	philo_act(t_args *input)
{
    int	i;

    // Initialize simulation state
    input->simulation_off = false;

    // Allocate memory for philosophers and forks
    if (init_memory(input) != 0)
        return;

    // Initialize mutexes
    if (init_mutexes(input) != 0)
    {
        free_memory(input);
        return;
    }

    // Initialize forks and philosophers
    init_forks(input);
    init_philosophers(input);

    // Set start time and create threads
    input->start_time = get_current_time();
    create_threads(input);

    // Monitor philosophers until simulation ends
    monitor_philosophers(input);

    // Join philosopher threads
    for (i = 0; i < input->philo_nbr; i++)
        pthread_join(input->philosophers[i].thread_id, NULL);

    // Clean up resources
    cleanup_resources(input);
}

void	cleanup_resources(t_args *input)
{
	int	i;

	i = 0;
	while (i < input->philo_nbr)
		pthread_mutex_destroy(&(input->forks[i++].fork_mutex));

	pthread_mutex_destroy(&input->print_mutex);
	pthread_mutex_destroy(&input->status_mutex);

	free(input->forks);
	free(input->philosophers);
}
