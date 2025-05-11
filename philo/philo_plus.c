/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:33:31 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/11 13:16:18 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
