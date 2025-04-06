/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:12:10 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/06 01:32:50 by riel-fas         ###   ########.fr       */
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

	// Check if number of arguments is either too low (< 5) or too high (> 6)
	if (ac < 5 || ac > 6)
	{
		printf("🚦ERROR🚦\n⛔️INPUT SHOULD BE : ./philo xx xxx xxx xxx [xxx]⛔️\n");
		return (1);
	}
	else
	{
		input_pars(ac, av, &input);
		philo_act(&input);
	}
	return (0);
}
