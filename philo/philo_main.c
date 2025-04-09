/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:12:10 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/09 16:03:54 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

////////////./philo xxx //// xxx //// xxx  //// xxx //// [x]/////////////a philosopher is a struct and forks are mutex
// int	main(int ac, char **av)
// {
// 	t_args input;


// 	if (ac > 5 || ac > 6)
// 	{
// 		// input_pars(&input, av);
// //
// 		// philo_act(&input);


// 		printf("[TRAFFIC LIGHT]ERROR[TRAFFIC LIGHT]\\n[NO ENTRY]INPUT SHOULD BE : ./philo xx xxx xxx xxx [xxx][NO ENTRY]");
// 	// 	dinner(&input);
// 		return (1);

// 	// 	free_leak(&input);
// 	}
// 	else
// 	{
// 		input_pars(ac, av, &input);
// 		philo_act(&input);

// 	}
// 	return (0);









// }

int	main(int ac, char **av)
{
	t_args input;


	if (ac < 5 || ac > 6)
	{
		printf("\033[1;31m┌───────────────────────────────────────────────────────────────┐\033[0m\n");
		printf("\033[1;31m│                 \033[0m🚦\033[1;31mERROR\033[0m\033[1;31m🚦                                     │\033[0m\n");
		printf("\033[1;31m│    \033[0m⛔️\033[1;33mINPUT SHOULD BE : ./philo x xx  xxx xxxx [xxx]⛔️         \033[0m\033[1;31m│\033[0m\n");
		printf("\033[1;31m│                                                               │\033[0m\n");
		printf("\033[1;31m│ \033[0mWhere:                                                        \033[1;31m│\033[0m\n");
		printf("\033[1;31m│ \033[0m- xx: number_of_philosophers and forks                        \033[1;31m│\033[0m\n");
		printf("\033[1;31m│ \033[0m- xx : time_to_die (in milliseconds)                          \033[1;31m│\033[0m\n");
		printf("\033[1;31m│ \033[0m- xxx: time_to_eat (in milliseconds)                          \033[1;31m│\033[0m\n");
		printf("\033[1;31m│ \033[0m- xxxx: time_to_sleep (in milliseconds)                       \033[1;31m│\033[0m\n");
		printf("\033[1;31m│ \033[0m- [xxx]: optional - number_of_times_each_philosopher_must_eat \033[1;31m│\033[0m\n");
		printf("\033[1;31m└───────────────────────────────────────────────────────────────┘\033[0m\n");
		return (1);
	}
	// Check the return value of input_pars
	if (input_pars(ac, av, &input) != 0)
	{
		return (1);
	}
	philo_act(&input);
	return (0);
}
