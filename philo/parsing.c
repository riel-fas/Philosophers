/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 03:30:56 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/06 00:22:17 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//in parsing we need to check with int max/min // get only the numbers // skip spaces // check for nehative


static	char	*check_input(char *input)
{
	int		x;
	char	*number;

	x = 0;
	while ((input[x] >= 9 && input[x] <= 13) || input[x] == 32)
		x++;
	if (input[x] == '+')
		x++;
	else if (input[x] == '-')
		error_mes_exit("		🚦ERROR🚦\n⛔️INPUT CANT BE NEGATIVE\n⛔️");
	if (!(input[x] >= '0' && input[x] <= '9'))
		error_mes_exit("		🚦ERROR🚦\n⛔️INPUT MUST BE NUMBERS\n⛔️");
	number = input + x;
	x = 0;
	while (number[x] >= '0' && number[x] <= '9')
		x++;
	if (x > 10)
		error_mes_exit("		🚦ERROR🚦\n⛔️THE INPUT IS BIGGER THAN INT_MAX⛔️");
	return (number);
}

// static long	atoi_v2(char *s)
// {
// 	int		x;
// 	long	result;

// 	s = check_input(s);
// 	result = 0;
// 	x = 0;  // Add initialization
// 	while (s[x] >= '0' && s[x] <= '9')
// 	{
// 		result = result * 10 + (s[x] - '0');
// 		x++;
// 	}
// 	if (result > INT_MAX)
// 		error_mes_exit("		🚦ERROR🚦\n⛔️INT_MAX IS THE LIMIT⛔️");
// 	return (result);
// }


static long	atoi_v2(char *s)
{
    int		x;
    long	result;

    s = check_input(s);
    result = 0;
    x = 0;
    
    while (s[x] >= '0' && s[x] <= '9')
    {
        result = result * 10 + (s[x] - '0');
        if (result > INT_MAX)
            error_mes_exit("ERROR: Value exceeds INT_MAX\n");
        x++;
    }
    
    return (result);
}

///////////////./philo xxx //// xxx //// xxx  //// xxx //// [x]/////////////a philosopher is a struct and forks are mutex

// void	input_pars(t_args *input, char **av)
// {
// 	input->philo_nbr = atoi_v2(av[1]);
// 	//in miliseconds
// 	input->time_to_die = atoi_v2(av[2]) * 1000;
// 	input->time_to_eat = atoi_v2(av[3]) * 1000;
// 	input->time_to_sleep = atoi_v2(av[4]) * 1000;

// 	if (input->time_to_die < 60000 || input->time_to_eat < 60000 || input->time_to_sleep < 60000)
// 		error_mes_exit("		🚦ERROR🚦\n⛔️TIME SHOULD BE MORE THAN 60 MILLI.SE.⛔️");
// 	if (av[5])
// 		input->meals_limit = atoi_v2(av[5]);
// 	else
// 		input->meals_limit = 0;
// }

void	input_pars(int ac, char **av, t_args *input)
{
    input->philo_nbr = atoi_v2(av[1]);
    if (input->philo_nbr <= 0)
        error_mes_exit("ERROR: Need at least 1 philosopher\n");

    input->time_to_die = atoi_v2(av[2]) * 1000; // Convert to microseconds
    input->time_to_eat = atoi_v2(av[3]) * 1000; // Convert to microseconds
    input->time_to_sleep = atoi_v2(av[4]) * 1000; // Convert to microseconds

    // Check for minimum time values
    if (input->time_to_die < 60000 || input->time_to_eat < 60000 ||
        input->time_to_sleep < 60000)
        error_mes_exit("ERROR: Time values must be at least 60ms\n");

    // Optional parameter: number of times each philosopher must eat
    if (ac == 6)
    {
        input->meals_limit = atoi_v2(av[5]);
        if (input->meals_limit <= 0)
            error_mes_exit("ERROR: Meals limit must be positive\n");
    }
    else
        input->meals_limit = -1; // No limit
}
