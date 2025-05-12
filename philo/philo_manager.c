/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:50:51 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/12 15:31:47 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_philos(t_philoinfo *info)
{
	int		i;
	t_philo	*philos;

	philos = malloc((info->philo_number) * sizeof(t_philo));
	if (!philos)
		return (0);
	i = 0;
	while (i < info->philo_number)
	{
		philos[i].id = i + 1;
		philos[i].pinfo = info;
		philos[i].sd.meals = 0;
		philos[i].is_full = 0;
		philos[i].r_fork = malloc(sizeof(pthread_mutex_t));
		if (!(philos[i].r_fork))
			return (free_philos(philos, info->philo_number));
		pthread_mutex_init(philos[i].r_fork, NULL);
		pthread_mutex_init(&philos[i].sd.last_meal_mutex, NULL);
		pthread_mutex_init(&philos[i].sd.meals_mutex, NULL);
		i++;
	}
	return (philos);
}

void	forks_assignement(t_philo *philos, t_philoinfo *info)
{
	int	i;

	i = 0;
	while (i < info->philo_number)
	{
		if (i == 0)
			philos[i].l_fork = philos[info->philo_number - 1].r_fork;
		else
			philos[i].l_fork = philos[i - 1].r_fork;
		i++;
	}
}

void	routine_start(t_philo *philos, t_philoinfo *info)
{
	int	i;

	i = 0;
	info->start_time = get_current_time();
	while (i < info->philo_number)
	{
		set_last_meal(&philos[i].sd);
		pthread_create(&(philos[i].thread), NULL, routine, &philos[i]);
		i++;
	}
}

void	join_threads(t_philo *philos, t_philoinfo *pinfo)
{
	int	i;

	i = 0;
	while (i < pinfo->philo_number)
		pthread_join(philos[i++].thread, NULL);
}
