/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:21:02 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/12 15:36:50 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_eat(t_philo *philo)
{
	t_philoinfo	*pinfo;

	pinfo = philo->pinfo;
	pthread_mutex_lock(philo->l_fork);
	safe_print(philo, FORK_TAKEN);
	pthread_mutex_lock(philo->r_fork);
	safe_print(philo, FORK_TAKEN);
	if (get_full(pinfo))
		return (0);
	safe_print(philo, EAT);
	set_last_meal(&philo->sd);
	precise_sleep(pinfo->time_to_eat, pinfo);
	increment_meals(&philo->sd);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (1);
}

int	ph_sleep(t_philo *philo)
{
	t_philoinfo	*pinfo;

	pinfo = philo->pinfo;
	if (get_full(pinfo))
		return (0);
	safe_print(philo, SLEEP);
	precise_sleep(pinfo->time_to_sleep, pinfo);
	return (1);
}

void	ph_think(t_philo *philo)
{
	safe_print(philo, THINK);
}

void	*routine(void *param)
{
	t_philo		*philo;
	t_philoinfo	*pinfo;

	philo = (t_philo *)param;
	pinfo = philo->pinfo;
	if (philo->id % 2 == 0)
		ph_sleep(philo);
	while (!get_died(pinfo) && !get_full(pinfo))
	{
		ph_think(philo);
		if (!ph_eat(philo))
			break ;
		if (!ph_sleep(philo))
			break ;
	}
	return (NULL);
}
