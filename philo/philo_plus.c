/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:33:31 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/29 11:33:34 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_mes_exit(char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		error_mes_exit("Error getting time");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_philosopher *philo, char *status)
{
	long	timestamp;
	int		should_print;

	pthread_mutex_lock(&philo->input->print_mutex);
	pthread_mutex_lock(&philo->input->status_mutex);
	should_print = !philo->input->simulation_off;
	pthread_mutex_unlock(&philo->input->status_mutex);
	if (should_print)
	{
		timestamp = get_current_time() - philo->input->start_time;
		printf("%ld %d %s\n", timestamp, philo->philo_id, status);
	}
	pthread_mutex_unlock(&philo->input->print_mutex);
}

void	precise_sleep(long milliseconds, t_args *input)
{
	long	start_time;
	int		should_continue;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < milliseconds)
	{
		pthread_mutex_lock(&input->status_mutex);
		should_continue = !input->simulation_off;
		pthread_mutex_unlock(&input->status_mutex);
		if (!should_continue)
			return;
		usleep(500);
	}
}
