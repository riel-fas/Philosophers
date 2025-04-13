/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 03:05:34 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/13 04:38:16 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_args	input;

	if (ac < 5 || ac > 6)
	{
		printf("\033[1;31m┌────────────────────────────────────────────────────────────┐\033[0m\n");
		printf("\033[1;31m│                 \033[0m🚦\033[1;31mERROR\033[0m\033[1;31m🚦                                    │\033[0m\n");
		printf("\033[1;31m│    \033[0m⛔️\033[1;33mINPUT SHOULD BE : ./philo x xx xxx xxxx [xxx]⛔️         \033[0m\033[1;31m│\033[0m\n");
		printf("\033[1;31m│                                                              │\033[0m\n");
		printf("\033[1;31m│ \033[0mWhere:                                                       \033[1;31m│\033[0m\n");
		printf("\033[1;31m│ \033[0m- xx: number_of_philosophers and forks                       \033[1;31m│\033[0m\n");
		printf("\033[1;31m│ \033[0m- xx : time_to_die (in milliseconds)                         \033[1;31m│\033[0m\n");
		printf("\033[1;31m│ \033[0m- xxx: time_to_eat (in milliseconds)                         \033[1;31m│\033[0m\n");
		printf("\033[1;31m│ \033[0m- xxxx: time_to_sleep (in milliseconds)                      \033[1;31m│\033[0m\n");
		printf("\033[1;31m│ \033[0m- [xxx]: optional - number_of_times_each_philosopher_must_eat\033[1;31m│\033[0m\n");
		printf("\033[1;31m└────────────────────────────────────────────────────────────┘\033[0m\n");
		return (1);
	}

	if (input_pars(ac, av, &input) != 0)
		return (1);

	philo_act(&input);
	return (0);
}
