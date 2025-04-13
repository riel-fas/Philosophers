/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 03:05:34 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/13 05:21:10 by riel-fas         ###   ########.fr       */
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
		if (pthread_create(&(input->philosophers[i].thread_id), NULL,
		                   philosopher_routine, &(input->philosophers[i])) != 0)
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

	// Initialize mutexes for thread safety
	pthread_mutex_init(&input->print_mutex, NULL);
	pthread_mutex_init(&input->status_mutex, NULL);

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

void	monitor_philosophers(t_args *input)
{
	int		i;
	int		all_full;
	long	current_time;
	long	time_since_meal;

	while (!input->simulation_off)
	{
		all_full = 1;
		i = 0;
		while (i < input->philo_nbr)
		{
			pthread_mutex_lock(&input->status_mutex);
			current_time = get_current_time();
			time_since_meal = current_time - input->philosophers[i].last_meal_time;
			pthread_mutex_unlock(&input->status_mutex);

			if (time_since_meal > input->time_to_die)
			{
				print_status(&input->philosophers[i], "died");
				pthread_mutex_lock(&input->print_mutex);
				input->simulation_off = true;
				pthread_mutex_unlock(&input->print_mutex);
				break;
			}

			pthread_mutex_lock(&input->status_mutex);
			if (input->meals_limit > 0 && input->philosophers[i].meal_count < input->meals_limit)
				all_full = 0;
			pthread_mutex_unlock(&input->status_mutex);

			i++;
		}
		if (input->meals_limit > 0 && all_full)
		{
			pthread_mutex_lock(&input->print_mutex);
			input->simulation_off = true;
			pthread_mutex_unlock(&input->print_mutex);
		}
		usleep(1000);
	}
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
