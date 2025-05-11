/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:34:15 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/11 12:20:04 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philosophers.h"

// void	pick_forks(t_philosopher *philo)
// {
// 	// Always pick the lower-numbered fork first to prevent deadlock
// 	if (philo->right_fork->fork_id < philo->left_fork->fork_id)
// 	{
// 		pthread_mutex_lock(&(philo->right_fork->fork_mutex));
// 		print_status(philo, "has taken a fork");
// 		pthread_mutex_lock(&(philo->left_fork->fork_mutex));
// 		print_status(philo, "has taken a fork");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&(philo->left_fork->fork_mutex));
// 		print_status(philo, "has taken a fork");
// 		pthread_mutex_lock(&(philo->right_fork->fork_mutex));
// 		print_status(philo, "has taken a fork");
// 	}
// }

// #include "philosophers.h"

// void	eat(t_philosopher *philo)
// {
// 	t_args	*input = philo->input;
// 	print_status(philo, "is eating");

// 	// Update last meal time and meal count as soon as eating starts
// 	pthread_mutex_lock(&input->status_mutex);
// 	philo->last_meal_time = get_current_time();
// 	philo->meal_count++;
// 	if (input->meals_limit > 0 && philo->meal_count >= input->meals_limit)
// 		philo->full = 1;
// 	pthread_mutex_unlock(&input->status_mutex);

// 	// Sleep for eating duration
// 	precise_sleep(input->time_to_eat, input);
// }

// // void	eat(t_philosopher *philo)
// // {
// // 	t_args	*input;

// // 	input = philo->input;
// // 	print_status(philo, "is eating");

// // 	// Update last meal time safely
// // 	pthread_mutex_lock(&input->status_mutex);
// // 	philo->last_meal_time = get_current_time();
// // 	pthread_mutex_unlock(&input->status_mutex);

// // 	// Sleep for eating duration
// // 	// precise_sleep(input->time_to_eat);
// // 	precise_sleep(input->time_to_eat, input);
// // 	// Update meal count safely
// // 	pthread_mutex_lock(&input->status_mutex);
// // 	philo->meal_count++;
// // 	if (input->meals_limit > 0 && philo->meal_count >= input->meals_limit)
// // 		philo->full = 1;
// // 	pthread_mutex_unlock(&input->status_mutex);
// // }

// void	release_forks(t_philosopher *philo)
// {
// 	pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
// 	pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
// 	print_status(philo, "is sleeping");
// 	precise_sleep(philo->input->time_to_sleep, philo->input);
// }

// void	*philosopher_routine(void *arg)
// {
// 	t_philosopher	*philo;
// 	t_args			*input;
// 	int				simulation_active;

// 	philo = (t_philosopher *)arg;
// 	input = philo->input;

// 	// Set last meal time to start time
// 	pthread_mutex_lock(&input->status_mutex);
// 	philo->last_meal_time = get_current_time();
// 	pthread_mutex_unlock(&input->status_mutex);

// 	// Handle single philosopher case
// 	if (input->philo_nbr == 1)
// 	{
// 		print_status(philo, "has taken a fork");
// 		precise_sleep(input->time_to_die, input);
// 		return (NULL);
// 	}

// 	// Stagger philosophers to prevent deadlock
// 	if (philo->philo_id % 2 == 0)
// 		precise_sleep(input->time_to_eat / 2, input);

// 	// Main philosopher loop
// 	while (1)
// 	{
// 		pthread_mutex_lock(&input->status_mutex);
// 		simulation_active = !input->simulation_off;
// 		pthread_mutex_unlock(&input->status_mutex);

// 		if (!simulation_active)
// 			break;

// 		print_status(philo, "is thinking");
// 		pick_forks(philo);

// 		pthread_mutex_lock(&input->status_mutex);
// 		simulation_active = !input->simulation_off;
// 		pthread_mutex_unlock(&input->status_mutex);

// 		if (!simulation_active)
// 		{
// 			pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
// 			pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
// 			break;
// 		}

// 		eat(philo);
// 		release_forks(philo);

// 		pthread_mutex_lock(&input->status_mutex);
// 		if (input->meals_limit > 0 && philo->meal_count >= input->meals_limit)
// 		{
// 			pthread_mutex_unlock(&input->status_mutex);
// 			break;
// 		}
// 		pthread_mutex_unlock(&input->status_mutex);
// 	}
// 	return (NULL);
// }

#include "philosophers.h"

static void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork->mutex);
    print_status(philo, FORK_TAKEN);
    pthread_mutex_lock(philo->right_fork->mutex);
    print_status(philo, FORK_TAKEN);

    print_status(philo, EATING);
    pthread_mutex_lock(&philo->shared.last_meal_mutex);
    philo->shared.last_meal = get_time();
    pthread_mutex_unlock(&philo->shared.last_meal_mutex);

    precise_sleep(philo->data->time_to_eat, philo->data);

    pthread_mutex_lock(&philo->shared.meal_mutex);
    philo->shared.meal_count++;
    if (philo->data->meal_limit > 0 &&
        philo->shared.meal_count >= philo->data->meal_limit)
        philo->full = true;
    pthread_mutex_unlock(&philo->shared.meal_mutex);

    pthread_mutex_unlock(philo->left_fork->mutex);
    pthread_mutex_unlock(philo->right_fork->mutex);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        usleep(1000);
    while (1)
    {
        pthread_mutex_lock(&philo->data->death_mutex);
        if (philo->data->sim_stop)
        {
            pthread_mutex_unlock(&philo->data->death_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->death_mutex);

        eat(philo);
        print_status(philo, SLEEPING);
        precise_sleep(philo->data->time_to_sleep, philo->data);
        print_status(philo, THINKING);
    }
    return (NULL);
}
