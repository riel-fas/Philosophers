/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 03:05:34 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/11 12:19:15 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	main(int ac, char **av)
// {
// 	t_args	input;

// 	if (ac < 5 || ac > 6)
// 	{
// 		printf("⛔️INPUT SHOULD BE : ./philo x xx xxx xxxx [xxx]⛔️\n");
// 		printf("Where:\n");
// 		printf("x: number_of_philosophers and forks\n");
// 		printf("xx : time_to_die (in milliseconds)\n");
// 		printf("xxx: time_to_eat (in milliseconds)\n");
// 		printf("xxxx: time_to_sleep (in milliseconds)\n");
// 		printf("[xxx]: optional - number_of_times_each_philosopher_must_eat\n");
// 		return (1);
// 	}
// 	if (input_pars(ac, av, &input) != 0)
// 		return (1);
// 	philo_act(&input);
// 	return (0);
// }


#include "philosophers.h"

int main(int ac, char **av)
{
    t_data  data;

    if (ac < 5 || ac > 6)
    {
        printf("Usage: %s number_of_philosophers time_to_die ", av[0]);
        printf("time_to_eat time_to_sleep [number_of_meals]\n");
        return (1);
    }
    if (init_data(&data, ac, av))
        return (1);
    if (init_philos(&data))
    {
        cleanup(&data);
        return (1);
    }
    monitor(&data);
    cleanup(&data);
    return (0);
}
