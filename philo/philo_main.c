/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:12:10 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/06 00:21:04 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

////////////./philo xxx //// xxx //// xxx  //// xxx //// [x]/////////////a philosopher is a struct and forks are mutex
int	main(int ac, char **av)
{
	t_args input;


	if (ac > 5 || ac > 6)
	{
		// input_pars(&input, av);
//
		// philo_act(&input);


		printf(""		🚦ERROR🚦\n⛔️INPUT SHOULD BE : ./philo xx xxx xxx xxx [xxx]⛔️"");
	// 	dinner(&input);
		return (1);

	// 	free_leak(&input);
	}
	else
	{
		input_pars(ac, av, &input);
		philo_act(&input);

	}
	return (0);
		// error_mes_exit("		🚦ERROR🚦\n⛔️INPUT SHOULD BE : ./philo xx xxx xxx xxx [xxx]⛔️");










}
