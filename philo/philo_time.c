/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:58:13 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/06 06:52:00 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Get current time in milliseconds
long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// Sleep for a specified number of milliseconds
// In philo_time.c
void precise_sleep(long milliseconds)
{
    long start = get_current_time();

    while ((get_current_time() - start) < milliseconds)
    {
        usleep(500); // Smaller sleep value for better precision
    }
}

// Print philosopher status with timestamp

