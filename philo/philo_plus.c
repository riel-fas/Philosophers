/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:33:31 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/11 15:35:36 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void set_last_meal_time(t_philosopher *philo)
// {
//     pthread_mutex_lock(&philo->last_meal_mutex);
//     philo->last_meal_time = get_current_time();
//     pthread_mutex_unlock(&philo->last_meal_mutex);
// }

// long get_last_meal_time(t_philosopher *philo)
// {
//     long time;

//     pthread_mutex_lock(&philo->last_meal_mutex);
//     time = philo->last_meal_time;
//     pthread_mutex_unlock(&philo->last_meal_mutex);
//     return (time);
// }

// void set_simulation_off(t_args *input, bool state)
// {
//     pthread_mutex_lock(&input->death_mutex);
//     input->simulation_off = state;
//     pthread_mutex_unlock(&input->death_mutex);
// }

// bool get_simulation_off(t_args *input)
// {
//     bool state;

//     pthread_mutex_lock(&input->death_mutex);
//     state = input->simulation_off;
//     pthread_mutex_unlock(&input->death_mutex);
//     return (state);
// }

// void set_philo_full(t_philosopher *philo, bool state)
// {
//     pthread_mutex_lock(&philo->meal_mutex);
//     philo->full = state;
//     pthread_mutex_unlock(&philo->meal_mutex);
// }

// bool get_philo_full(t_philosopher *philo)
// {
//     bool state;

//     pthread_mutex_lock(&philo->meal_mutex);
//     state = philo->full;
//     pthread_mutex_unlock(&philo->meal_mutex);
//     return (state);
// }


#include "philosophers.h"

void	safe_print(t_philo *philo, t_status status)
{
	t_pinfo	*pinfo;

	pinfo = philo->pinfo;
	pthread_mutex_lock(pinfo->print_mutex);
	if (!get_died(pinfo) || status == DIED)
	{
		printf("%lu %i ", program_time(pinfo->start_time), philo->id);
		if (status == FORK_TAKEN)
			printf("has taken a fork\n");
		else if (status == EAT)
			printf("is eating\n");
		else if (status == SLEEP)
			printf("is sleeping\n");
		else if (status == THINK)
			printf("is thinking\n");
		else if (status == DIED)
			printf("died\n");
	}
	pthread_mutex_unlock(pinfo->print_mutex);
}

#include "philosophers.h"

void	clear_mutexes(t_philo *philos)
{
	int		i;
	t_pinfo	*pinfo;

	pinfo = philos[0].pinfo;
	i = 0;
	while (i < pinfo->pnumber)
	{
		pthread_mutex_destroy(philos[i].r_fork);
		pthread_mutex_destroy(&philos[i].sd.last_meal_mutex);
		pthread_mutex_destroy(&philos[i].sd.meals_mutex);
		i++;
	}
	pthread_mutex_destroy(pinfo->print_mutex);
	pthread_mutex_destroy(pinfo->died_mutex);
	pthread_mutex_destroy(pinfo->full_mutex);
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

void	free_resources(t_philo *philos, t_pinfo *pinfo)
{
	free(pinfo->print_mutex);
	free(pinfo->died_mutex);
	free(pinfo->full_mutex);
	free_philos(philos, pinfo->pnumber);
	free(pinfo);
}

void	unlock_mutexes(t_philo *philos)
{
	int		i;
	t_pinfo	*pinfo;

	pinfo = philos[0].pinfo;
	i = 0;
	while (i < pinfo->pnumber)
	{
		pthread_mutex_unlock(philos[i].r_fork);
		pthread_mutex_unlock(philos[i].l_fork);
		i++;
	}
	pthread_mutex_unlock(pinfo->print_mutex);
	pthread_mutex_unlock(pinfo->died_mutex);
	pthread_mutex_unlock(pinfo->full_mutex);
}
