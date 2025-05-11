/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:33:31 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/11 12:21:01 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	error_mes_exit(char *error)
// {
// 	printf("%s\n", error);
// 	exit(EXIT_FAILURE);
// }

// long	get_current_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) != 0)
// 		error_mes_exit("Error getting time");
// 	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
// }

// void	print_status(t_philosopher *philo, char *status)
// {
// 	long	timestamp;
// 	int		should_print;

// 	pthread_mutex_lock(&philo->input->print_mutex);
// 	pthread_mutex_lock(&philo->input->status_mutex);
// 	should_print = !philo->input->simulation_off;
// 	pthread_mutex_unlock(&philo->input->status_mutex);
// 	if (should_print)
// 	{
// 		timestamp = get_current_time() - philo->input->start_time;
// 		printf("%ld %d %s\n", timestamp, philo->philo_id, status);
// 	}
// 	pthread_mutex_unlock(&philo->input->print_mutex);
// }

// void	precise_sleep(long milliseconds, t_args *input)
// {
//     long	start_time;
//     long	elapsed;
//     int		should_continue;

//     start_time = get_current_time();
//     while (1)
//     {
//         pthread_mutex_lock(&input->status_mutex);
//         should_continue = !input->simulation_off;
//         pthread_mutex_unlock(&input->status_mutex);

//         if (!should_continue)
//             return;

//         elapsed = get_current_time() - start_time;
//         if (elapsed >= milliseconds)
//             return;

//         // More precise sleep intervals
//         usleep(500);
//     }
// }


void set_last_meal_time(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->last_meal_mutex);
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philo->last_meal_mutex);
}

long get_last_meal_time(t_philosopher *philo)
{
    long time;

    pthread_mutex_lock(&philo->last_meal_mutex);
    time = philo->last_meal_time;
    pthread_mutex_unlock(&philo->last_meal_mutex);
    return (time);
}

void set_simulation_off(t_args *input, bool state)
{
    pthread_mutex_lock(&input->death_mutex);
    input->simulation_off = state;
    pthread_mutex_unlock(&input->death_mutex);
}

bool get_simulation_off(t_args *input)
{
    bool state;

    pthread_mutex_lock(&input->death_mutex);
    state = input->simulation_off;
    pthread_mutex_unlock(&input->death_mutex);
    return (state);
}

void set_philo_full(t_philosopher *philo, bool state)
{
    pthread_mutex_lock(&philo->meal_mutex);
    philo->full = state;
    pthread_mutex_unlock(&philo->meal_mutex);
}

bool get_philo_full(t_philosopher *philo)
{
    bool state;

    pthread_mutex_lock(&philo->meal_mutex);
    state = philo->full;
    pthread_mutex_unlock(&philo->meal_mutex);
    return (state);
}
