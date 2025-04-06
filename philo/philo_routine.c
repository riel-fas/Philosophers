/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 00:00:14 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/06 03:24:24 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Function to handle fork picking
void	pick_forks(t_philosopher *philo)
{
    // Always pick the lower-numbered fork first to prevent deadlock
	if (philo->right_fork->fork_id < philo->left_fork->fork_id)
	{
		pthread_mutex_lock(&(philo->right_fork->fork_mutex));
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->left_fork->fork_mutex));
	print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(philo->left_fork->fork_mutex));
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->right_fork->fork_mutex));
		print_status(philo, "has taken a fork");
    }
}

// Function to handle eating
// Function to handle eating
// void	eat(t_philosopher *philo)
// {
// 	t_args *input = philo->input;
// 	print_status(philo, "is eating");
//     // Update last meal time
// 	philo->last_meal_time = get_current_time();
//     // Sleep for time_to_eat milliseconds
// 	precise_sleep(input->time_to_eat / 1000); // Convert microseconds to milliseconds
//     // Increment meal count
// 	philo->meal_count++;
//     // Check if philosopher is full
// 	if (input->meals_limit > 0 && philo->meal_count >= input->meals_limit)
// 		philo->full = 1;
// }

// // Function to handle fork releasing
// void	release_forks(t_philosopher *philo)
// {
// 	pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
// 	pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
// 	print_status(philo, "is sleeping");
// 	precise_sleep(philo->input->time_to_sleep / 1000); // Convert microseconds to milliseconds
// }

void	eat(t_philosopher *philo)
{
	t_args *input = philo->input;
	print_status(philo, "is eating");
	// Update last meal time
	philo->last_meal_time = get_current_time();
	// Remove the division by 1000
	precise_sleep(input->time_to_eat);
	// Increment meal count
	philo->meal_count++;
	// Check if philosopher is full
	if (input->meals_limit > 0 && philo->meal_count >= input->meals_limit)
		philo->full = 1;
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
	pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
	print_status(philo, "is sleeping");
	// Remove the division by 1000
	precise_sleep(philo->input->time_to_sleep);
}


// Main routine for each philosopher
void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_args			*input;

	philo = (t_philosopher *)arg;
	input = philo->input;
    // Set initial last meal time to start time
	philo->last_meal_time = get_current_time();

	// Stagger philosopher start times to reduce contention
	if (philo->philo_id % 2 == 0)
		usleep(1000); // Small delay for even-numbered philosophers
    // Continue until simulation ends
	while (!input->simulation_off)
	{
        // Thinking state
		print_status(philo, "is thinking");
        // Eating state (includes picking up forks)
		pick_forks(philo);
		eat(philo);
		release_forks(philo);
        // Check if philosopher is full
		if (philo->full)
			break;
	}
	return (NULL);
}
