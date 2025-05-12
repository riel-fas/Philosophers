/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:58:13 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/12 15:37:02 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_current_time(void)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	return ((ct.tv_sec * 1000) + (ct.tv_usec / 1000));
}

unsigned long	program_time(long start_time)
{
	return (get_current_time() - start_time);
}

void	precise_sleep(unsigned long ms, t_philoinfo *pinfo)
{
	unsigned long	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < ms && !get_died(pinfo))
		usleep(100);
}
