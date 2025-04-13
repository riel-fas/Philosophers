/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 03:05:34 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/13 05:09:40 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_args	input;

	if (ac < 5 || ac > 6)
	{
		printf("⛔️INPUT SHOULD BE : ./philo x xx xxx xxxx [xxx]⛔️\n");
		printf("Where:\n");
		printf("x: number_of_philosophers and forks\n");
		printf("xx : time_to_die (in milliseconds)\n");
		printf("xxx: time_to_eat (in milliseconds)\n");
		printf("xxxx: time_to_sleep (in milliseconds)\n");
		printf("[xxx]: optional - number_of_times_each_philosopher_must_eat\n");
		return (1);
	}
	if (input_pars(ac, av, &input) != 0)
		return (1);
	philo_act(&input);
	return (0);
}
