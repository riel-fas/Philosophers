/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 03:05:34 by riel-fas          #+#    #+#             */
/*   Updated: 2025/06/05 16:46:18 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ll()
{
	system("leaks -q philo");

}

int	main(int ac, char **av)
{
	t_philoinfo	*infos;
	t_philo		*philos;

	atexit(ll);

	if (ac < 5 || ac > 6)
	{
		printf("⛔️INPUT SHOULD BE : ./philo x xx xxx xxxx [xxx]⛔️\n");
		printf("x: number_of_philosophers and forks\n");
		printf("xx : time_to_die (in milliseconds)\n");
		printf("xxx: time_to_eat (in milliseconds)\n");
		printf("xxxx: time_to_sleep (in milliseconds)\n");
		printf("[xxx]: optional - number_of_times_each_philosopher_must_eat\n");
		return (EXIT_FAILURE);
	}
	if (!philo_init(&infos, ac - 1, av + 1))
		return (EXIT_FAILURE);
	philos = create_philos(infos);
	if (!philos)
		return (EXIT_FAILURE);
	forks_assignement(philos, infos);
	routine_start(philos, infos);
	monitor(philos);
	join_threads(philos, infos);
	clear_mutexes(philos);
	free_resources(philos, infos);
	return (EXIT_SUCCESS);
}
