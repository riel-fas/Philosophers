/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:51:57 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/06 03:10:52 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	init_forks(t_args *input)
{
	int	x;

	x = 0;
	while (x < input->philo_nbr)
	{
		//we create a mutex
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
		input->philosophers[x].last_meal_time = 0;
		input->philosophers[x].right_fork = &input->forks[x];
		//to avoid overlap we use % //the left is the next one
		input->philosophers[x].left_fork = &input->forks[(x + 1) % input->philo_nbr];
		x++;
	}
}

void	create_threads(t_args *input)
{
	int i;

	i = 0;
	while (i < input->philo_nbr)
	{
		if (pthread_create(&(input->philosophers[i].thread_id), NULL, philosopher_routine, &(input->philosophers[i])) != 0)
		{
			input->simulation_off = true;
			error_mes_exit("THREAD CREATION ERROR\n");
		}
		i++;
	}
}

void	philo_act(t_args *input)
{
	int	i;

	input->simulation_off = false;
	input->philosophers = malloc(sizeof(t_philosopher) * input->philo_nbr);
	if (!input->philosophers)
		error_mes_exit("MALLOC ERROR\n");
	input->forks = malloc(sizeof(t_fork) * input->philo_nbr);
	if (!input->forks)
	{
		free(input->philosophers);
		error_mes_exit("MALLOC ERROR\n");
	}
	init_forks(input);
	init_philosophers(input);
    // Set start time before creating threads
	input->start_time = get_current_time();
    // Link each philosopher back to the input struct
	i = 0;
	while (i < input->philo_nbr)
	{
		input->philosophers[i].input = input;
		i++;
	}
	create_threads(input);
    // Monitor for death or completion
	monitor_philosophers(input);
    // Join all threads once simulation is over
	i = 0;
	while (i < input->philo_nbr)
		pthread_join(input->philosophers[i++].thread_id, NULL);
    // Cleanup resources
	cleanup_resources(input);
}

// // Add a new function to clean up resources
// void	cleanup_resources(t_args *input)
// {
//     int	i;

//     // Destroy all fork mutexes
//     i = 0;
//     while (i < input->philo_nbr)
//         pthread_mutex_destroy(&(input->forks[i++].fork_mutex));

//     // Free allocated memory
//     free(input->forks);
//     free(input->philosophers);
// }

// Monitor philosophers for death and completion
// void	monitor_philosophers(t_args *input)
// {
// 	int		i;
// 	int		all_full;
// 	long	current_time;

// 	while (!input->simulation_off)
// 	{
// 		i = 0;
// 		all_full = 1;
//         // Check each philosopher
// 		while (i < input->philo_nbr)
// 		{
// 			current_time = get_current_time();
//             // Check if philosopher died (time since last meal > time_to_die)
// 			if ((current_time - input->philosophers[i].last_meal_time) >
// 				(input->time_to_die / 1000))
// 			{
// 				printf("%ld %d died\n", current_time - input->start_time, input->philosophers[i].philo_id);
// 				input->simulation_off = true;
// 				break;
// 			}
//             // Check if all philosophers are full
// 			if (input->meals_limit > 0 && !input->philosophers[i].full)
// 				all_full = 0;
// 			i++;
// 		}
//         // If all philosophers are full, end simulation
// 		if (input->meals_limit > 0 && all_full)
// 			input->simulation_off = true;
//         // Short sleep to avoid wasting CPU
//         usleep(1000);
//     }
// }

void	monitor_philosophers(t_args *input)
{
	int		i;
	int		all_full;
	long	current_time;

	while (!input->simulation_off)
	{
		i = 0;
		all_full = 1;
		// Check each philosopher
		while (i < input->philo_nbr)
		{
			current_time = get_current_time();
			// Check if philosopher died - use time_to_die directly, not divided
			if ((current_time - input->philosophers[i].last_meal_time) > input->time_to_die)
			{
				printf("%ld %d died\n", current_time - input->start_time, input->philosophers[i].philo_id);
				input->simulation_off = true;
				break;
			}
			// Check if all philosophers are full
			if (input->meals_limit > 0 && !input->philosophers[i].full)
				all_full = 0;
			i++;
		}
		// If all philosophers are full, end simulation
		if (input->meals_limit > 0 && all_full)
			input->simulation_off = true;
		// Short sleep to avoid wasting CPU
		usleep(1000);
	}
}


// Clean up resources
void	cleanup_resources(t_args *input)
{
	int	i;

    // Destroy all fork mutexes
	i = 0;
	while (i < input->philo_nbr)
		pthread_mutex_destroy(&(input->forks[i++].fork_mutex));
    // Free allocated memory
	free(input->forks);
	free(input->philosophers);
}
