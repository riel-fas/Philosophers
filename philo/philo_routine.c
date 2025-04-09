/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 00:00:14 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/09 09:41:51 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Function to handle fork picking
void pick_forks(t_philosopher *philo)
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

void eat(t_philosopher *philo)
{
    t_args *input = philo->input;
    print_status(philo, "is eating");
    // Update last meal time
    philo->last_meal_time = get_current_time();
    precise_sleep(input->time_to_eat);
    // Increment meal count
    philo->meal_count++;
    // Check if philosopher is full
    if (input->meals_limit > 0 && philo->meal_count >= input->meals_limit)
        philo->full = 1;
}

void release_forks(t_philosopher *philo)
{
    pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
    pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
    print_status(philo, "is sleeping");
    precise_sleep(philo->input->time_to_sleep);
}


// Main routine for each philosopher
void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_args *input = philo->input;

    // Set last meal time to start time
    philo->last_meal_time = get_current_time();
    // Handle single philosopher case
    if (input->philo_nbr == 1)
    {
        print_status(philo, "has taken a fork");
        precise_sleep(input->time_to_die);
        return NULL;
    }
    // Stagger philosophers - more effectively
    if (philo->philo_id % 2 == 0)
        precise_sleep(input->time_to_eat / 2);

    while (!input->simulation_off)
    {
        print_status(philo, "is thinking");

        // Don't continue if simulation is off
        if (input->simulation_off)
            break;

        pick_forks(philo);

        // Check again before eating
        if (input->simulation_off) {
            pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
            pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
            break;
        }

        eat(philo);
        release_forks(philo);

        // Break if philosopher is full
        if (input->meals_limit > 0 && philo->meal_count >= input->meals_limit)
            break;
    }
    return (NULL);
}
