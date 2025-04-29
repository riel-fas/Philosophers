/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:50:51 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/29 11:44:59 by riel-fas         ###   ########.fr       */
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
	if (pthread_mutex_init(&input->print_mutex, NULL) != 0)
	{
		free(input->philosophers);
		free(input->forks);
		error_mes_exit("PRINT MUTEX INIT ERROR\n");
	}
	if (pthread_mutex_init(&input->status_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&input->print_mutex);
		free(input->philosophers);
		free(input->forks);
		error_mes_exit("STATUS MUTEX INIT ERROR\n");
	}
	init_forks(input);
	init_philosophers(input);
	input->start_time = get_current_time();
	create_threads(input);
	monitor_philosophers(input);
	for (i = 0; i < input->philo_nbr; i++)
	{
		pthread_join(input->philosophers[i].thread_id, NULL);
	}
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
