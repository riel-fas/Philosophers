/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:33:31 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/12 15:36:41 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear_mutexes(t_philo *philos)
{
	int			i;
	t_philoinfo	*pinfo;

	pinfo = philos[0].pinfo;
	i = 0;
	while (i < pinfo->philo_number)
	{
		pthread_mutex_destroy(philos[i].r_fork);
		pthread_mutex_destroy(&philos[i].sd.last_meal_mutex);
		pthread_mutex_destroy(pinfo->print_mutex);
		pthread_mutex_destroy(pinfo->died_mutex);
		pthread_mutex_destroy(pinfo->full_mutex);
		i++;
	}
}

void	*free_philos(t_philo *philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(philos[i++].r_fork);
	free(philos);
	return (NULL);
}

void	free_resources(t_philo *philos, t_philoinfo *pinfo)
{
	free(pinfo->print_mutex);
	free(pinfo->died_mutex);
	free(pinfo->full_mutex);
	free_philos(philos, pinfo->philo_number);
	free(pinfo);
}

void	unlock_mutexes(t_philo *philos)
{
	int			i;
	t_philoinfo	*pinfo;

	pinfo = philos[0].pinfo;
	i = 0;
	while (i < pinfo->philo_number)
	{
		pthread_mutex_unlock(philos[i].r_fork);
		pthread_mutex_unlock(philos[i].pinfo->died_mutex);
		pthread_mutex_unlock(philos[i].pinfo->full_mutex);
		pthread_mutex_unlock(philos[i].pinfo->print_mutex);
		i++;
	}
}

void	safe_print(t_philo *philo, t_stats status)
{
	t_philoinfo	*pinfo;

	pinfo = philo->pinfo;
	pthread_mutex_lock(pinfo->print_mutex);
	if (status == FORK_TAKEN && !get_died(pinfo))
		printf("%ld %i has taken a fork\n", program_time(pinfo->start_time),
			philo->id);
	else if (status == EAT && !get_died(pinfo))
		printf("%ld %i is eating\n", program_time(pinfo->start_time),
			philo->id);
	else if (status == SLEEP && !get_died(pinfo))
		printf("%ld %i is sleeping\n", program_time(pinfo->start_time),
			philo->id);
	else if (status == THINK && !get_died(pinfo))
		printf("%ld %i is thinking\n", program_time(pinfo->start_time),
			philo->id);
	else if (status == DIED)
		printf("%ld %i died\n", program_time(pinfo->start_time), philo->id);
	pthread_mutex_unlock(pinfo->print_mutex);
}
