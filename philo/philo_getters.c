/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:18:16 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/12 15:31:33 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_last_meal(t_data *sd)
{
	long long	last_meal;

	pthread_mutex_lock(&sd->last_meal_mutex);
	last_meal = sd->last_meal;
	pthread_mutex_unlock(&sd->last_meal_mutex);
	return (last_meal);
}

int	get_died(t_philoinfo *pinfo)
{
	int	x;

	pthread_mutex_lock(pinfo->died_mutex);
	x = pinfo->died;
	pthread_mutex_unlock(pinfo->died_mutex);
	return (x);
}

int	get_meals(t_data *sd)
{
	int	meals;

	pthread_mutex_lock(&sd->meals_mutex);
	meals = sd->meals;
	pthread_mutex_unlock(&sd->meals_mutex);
	return (meals);
}

int	get_full(t_philoinfo *pinfo)
{
	int	is_full;

	pthread_mutex_lock(pinfo->full_mutex);
	is_full = pinfo->full;
	pthread_mutex_unlock(pinfo->full_mutex);
	return (is_full);
}
