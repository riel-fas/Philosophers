/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:58:13 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/05 23:58:25 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

// Get current time in milliseconds
long	get_current_time(void)
{
    struct timeval	time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// Sleep for a specified number of milliseconds
void	precise_sleep(long milliseconds)
{
    long	start_time;
    long	current_time;

    start_time = get_current_time();
    while (1)
    {
        current_time = get_current_time();
        if (current_time - start_time >= milliseconds)
            break;
        usleep(500); // Sleep in small increments for more precision
    }
}

// Print philosopher status with timestamp
void	print_status(t_philosopher *philo, char *status)
{
    long	current_time;
    // We need this pointer to access global state
    t_args	*input = philo->input;

    // Don't print if simulation is over
    if (input->simulation_off)
        return;

    current_time = get_current_time() - input->start_time;
    printf("%ld %d %s\n", current_time, philo->philo_id, status);
}
