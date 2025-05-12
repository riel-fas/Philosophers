/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:51:32 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/12 15:36:03 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_check(t_philo *philos)
{
	int			i;
	t_philoinfo	*pinfo;

	i = 0;
	pinfo = philos[0].pinfo;
	while (i < pinfo->philo_number)
	{
		if (get_current_time() - get_last_meal(&philos[i].sd)
			>= pinfo->time_to_die)
		{
			set_died(pinfo, 1);
			safe_print(&philos[i], DIED);
			return (0);
		}
		i++;
	}
	return (1);
}

int	meals_check(t_philo *philos, int *full)
{
	int			i;
	t_philoinfo	*pinfo;

	i = 0;
	pinfo = philos[0].pinfo;
	if (pinfo->meal_limit == -1)
		return (1);
	while (i < pinfo->philo_number)
	{
		if (get_meals(&philos[i].sd) >= pinfo->meal_limit && !philos[i].is_full)
		{
			philos[i].is_full = 1;
			(*full)++;
		}
		if ((*full) >= pinfo->philo_number)
		{
			set_full(pinfo, 1);
			return (0);
		}
		i++;
	}
	return (1);
}

void	*monitor(void *param)
{
	t_philo		*philos;
	t_philoinfo	*pinfo;
	int			full;

	full = 0;
	philos = (t_philo *)param;
	pinfo = philos[0].pinfo;
	while (!get_died(pinfo) && meals_check(philos, &full))
		death_check(philos);
	unlock_mutexes(philos);
	return (NULL);
}
