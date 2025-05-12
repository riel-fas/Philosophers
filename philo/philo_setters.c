/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:18:30 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/12 15:18:31 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_last_meal(t_data *sd)
{
	pthread_mutex_lock(&sd->last_meal_mutex);
	sd->last_meal = get_current_time();
	pthread_mutex_unlock(&sd->last_meal_mutex);
}

void	set_died(t_philoinfo *pinfo, int boolean)
{
	pthread_mutex_lock(pinfo->died_mutex);
	pinfo->died = boolean;
	pthread_mutex_unlock(pinfo->died_mutex);
}

void	increment_meals(t_data *sd)
{
	pthread_mutex_lock(&sd->meals_mutex);
	sd->meals++;
	pthread_mutex_unlock(&sd->meals_mutex);
}

void	set_full(t_philoinfo *pinfo, int is_full)
{
	pthread_mutex_lock(pinfo->full_mutex);
	pinfo->full = is_full;
	pthread_mutex_unlock(pinfo->full_mutex);
}
