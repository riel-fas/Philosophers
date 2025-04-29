/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:25:31 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/29 09:07:06 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_resources(t_args *input)
{
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
}

void	init_mutexes(t_args *input)
{
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
}

void	start_simulation(t_args *input)
{
	init_forks(input);
	init_philosophers(input);
	input->start_time = get_current_time();
	create_threads(input);
	monitor_philosophers(input);
}
