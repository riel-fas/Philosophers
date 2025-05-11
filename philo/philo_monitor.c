/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:51:32 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/11 09:56:52 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitor_philosophers(t_args *input)
{
    int		i;
    int		full_philos;
    long	now;
    long	time_since_meal;

    while (1)
    {
        full_philos = 0;
        i = 0;
        while (i < input->philo_nbr)
        {
            pthread_mutex_lock(&input->status_mutex);
            // Check if simulation already ended
            if (input->simulation_off)
            {
                pthread_mutex_unlock(&input->status_mutex);
                return;
            }

            // Check if this philosopher is full
            if (input->meals_limit > 0 && input->philosophers[i].meal_count >= input->meals_limit)
                full_philos++;

            // Check death condition
            now = get_current_time();
            time_since_meal = now - input->philosophers[i].last_meal_time;

            if (time_since_meal > input->time_to_die)
            {
                input->simulation_off = true;
                pthread_mutex_unlock(&input->status_mutex);

                pthread_mutex_lock(&input->print_mutex);
                printf("%ld %d %s\n", now - input->start_time,
                    input->philosophers[i].philo_id, "died");
                pthread_mutex_unlock(&input->print_mutex);
                return;
            }
            pthread_mutex_unlock(&input->status_mutex);
            i++;
        }

        // Check if all philosophers are full
        pthread_mutex_lock(&input->status_mutex);
        if (input->meals_limit > 0 && full_philos == input->philo_nbr)
        {
            input->simulation_off = true;
            pthread_mutex_unlock(&input->status_mutex);
            return;
        }
        pthread_mutex_unlock(&input->status_mutex);

        // Less aggressive sleeping to spot deaths quicker
        usleep(500);
    }
}




// // Check if a philosopher has died
// static int	check_philosopher_death(t_args *input, int i)
// {
// 	long	now;
// 	long	time_since_meal;

// 	pthread_mutex_lock(&input->status_mutex);
// 	now = get_current_time();
// 	time_since_meal = now - input->philosophers[i].last_meal_time;
// 	if (!input->simulation_off && time_since_meal > input->time_to_die)
// 	{
// 		input->simulation_off = true;
// 		pthread_mutex_unlock(&input->status_mutex);
// 		pthread_mutex_lock(&input->print_mutex);
// 		printf("%ld %d %s\n", now - input->start_time, input->philosophers[i].philo_id, "died");
// 		pthread_mutex_unlock(&input->print_mutex);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&input->status_mutex);
// 	return (0);
// }

// // Check if all philosophers are full
// static int	check_all_philosophers_full(t_args *input)
// {
// 	int	i;
// 	int	full_philos;

// 	full_philos = 0;
// 	i = 0;
// 	while (i < input->philo_nbr)
// 	{
// 		pthread_mutex_lock(&input->status_mutex);
// 		if (input->meals_limit > 0 && input->philosophers[i].meal_count >= input->meals_limit)
// 			full_philos++;
// 		pthread_mutex_unlock(&input->status_mutex);
// 		i++;
// 	}
// 	return (full_philos == input->philo_nbr);
// }


// void	monitor_philosophers(t_args *input)
// {
// 	int	i;

// 	while (1)
// 	{
// 		i = 0;
// 		while (i < input->philo_nbr)
// 		{
// 			if (check_philosopher_death(input, i))
// 				return ;
// 			i++;
// 		}
// 		pthread_mutex_lock(&input->status_mutex);
// 		if (input->meals_limit > 0 && check_all_philosophers_full(input))
// 		{
// 			input->simulation_off = true;
// 			pthread_mutex_unlock(&input->status_mutex);
// 			return ;
// 		}
// 		pthread_mutex_unlock(&input->status_mutex);
// 		usleep(1000);
// 	}
// }



///////////////////////////norminette checked//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////




// static int	check_philosopher_death(t_args *input, int i)
// {
// 	long	now;
// 	long	time_since_meal;

// 	now = get_current_time();
// 	time_since_meal = now - input->philosophers[i].last_meal_time;
// 	if (!input->simulation_off && time_since_meal > input->time_to_die)
// 	{
// 		input->simulation_off = true;
// 		pthread_mutex_unlock(&input->status_mutex);
// 		pthread_mutex_lock(&input->print_mutex);
// 		printf("%ld %d %s\n", now - input->start_time, input->philosophers[i].philo_id, "died");
// 		pthread_mutex_unlock(&input->print_mutex);
// 		return (1);
// 	}
// 	return (0);
// }

// static int	check_all_philos_full(t_args *input, int full_philos)
// {
// 	if (input->meals_limit > 0 && full_philos == input->philo_nbr)
// 	{
// 		input->simulation_off = true;
// 		pthread_mutex_unlock(&input->status_mutex);
// 		return (1);
// 	}
// 	return (0);
// }

// void	monitor_philosophers(t_args *input)
// {
// 	int	i;
// 	int	full_philos;

// 	while (1)
// 	{
// 		full_philos = 0;
// 		i = -1;
// 		while (++i < input->philo_nbr)
// 		{
// 			pthread_mutex_lock(&input->status_mutex);
// 			if (input->meals_limit > 0 && input->philosophers[i].meal_count >= input->meals_limit)
// 				full_philos++;
// 			if (check_philosopher_death(input, i))
// 				return ;
// 			pthread_mutex_unlock(&input->status_mutex);
// 		}
// 		pthread_mutex_lock(&input->status_mutex);
// 		if (check_all_philos_full(input, full_philos))
// 			return ;
// 		pthread_mutex_unlock(&input->status_mutex);
// 		usleep(1000);
// 	}
// }
