/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:25:31 by riel-fas          #+#    #+#             */
/*   Updated: 2025/06/05 18:03:13 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mutexes_init(t_philoinfo *info)
{
	info->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!info->print_mutex)
		return (0);
	info->died_mutex = malloc(sizeof(pthread_mutex_t));
	if (!info->died_mutex)
	{
		pthread_mutex_destroy(info->print_mutex);
		return (0);
	}
	info->full_mutex = malloc(sizeof(pthread_mutex_t));
	if (!info->full_mutex)
	{
		pthread_mutex_destroy(info->print_mutex);
		pthread_mutex_destroy(info->died_mutex);
		return (0);
	}
	pthread_mutex_init(info->print_mutex, NULL);
	pthread_mutex_init(info->died_mutex, NULL);
	pthread_mutex_init(info->full_mutex, NULL);
	return (1);
}

int	philo_init(t_philoinfo **info, int count, char **data)
{
	int	error_found;

	error_found = 0;
	if (count < 4 || count > 5)
		return (0);
	*info = malloc(sizeof(t_philoinfo));
	if (!*info)
		return (0);
	**info = (t_philoinfo){0};
	(*info)->philo_number = ft_atoi(data[0], &error_found);
	if (!validate_philo_number(info))
		return (0);
	(*info)->time_to_die = ft_atoi(data[1], &error_found);
	(*info)->time_to_eat = ft_atoi(data[2], &error_found);
	(*info)->time_to_sleep = ft_atoi(data[3], &error_found);
	if (data[4])
		(*info)->meal_limit = ft_atoi(data[4], &error_found);
	else
		(*info)->meal_limit = -1;
	if (!check_errors(*info, data[4], error_found))
		return (0);
	mutexes_init((*info));
	return (1);
}

int	validate_philo_number(t_philoinfo **info)
{
	if ((*info)->philo_number <= 0)
	{
		free(*info);
		return (0);
	}
	return (1);
}
