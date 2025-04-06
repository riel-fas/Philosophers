/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 03:12:13 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/06 01:33:22 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	error_mes_exit(char *error)
// {
// 	printf("%s\n", error);
// 	exit(EXIT_FAILURE);
// }

// // // Get current time in milliseconds
// // long	get_current_time(void)
// // {
// // 	struct timeval	time;

// // 	gettimeofday(&time, NULL);
// // 	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
// // }

// void	print_status(t_philosopher *philo, char *status)
// {
// 	long	current_time;
//     // We need this pointer to access global state
// 	t_args	*input = philo->input;

//     // Don't print if simulation is over
// 	if (input->simulation_off)
// 		return;
// 	current_time = get_current_time() - input->start_time;
// 	printf("%ld %d %s\n", current_time, philo->philo_id, status);
// }

void	error_mes_exit(char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

// Get current time in milliseconds
long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// Function for precise sleeping
void	precise_sleep(long milliseconds)
{
	long	start;
	long	elapsed;

	start = get_current_time();
	while (1)
	{
		elapsed = get_current_time() - start;
		if (elapsed >= milliseconds)
			break;
		usleep(100);  // Sleep for small intervals to reduce CPU usage
	}
}

// Function to print status messages
void	print_status(t_philosopher *philo, char *status)
{
	long	current_time;

	if (philo->input->simulation_off)
		return;  // Don't print if simulation has ended

	current_time = get_current_time();
	printf("%ld %d %s\n",
		current_time - philo->input->start_time,
		philo->philo_id,
		status);
}
