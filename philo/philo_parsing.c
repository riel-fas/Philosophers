/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 03:30:56 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/06 03:13:34 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//in parsing we need to check with int max/min // get only the numbers // skip spaces // check for nehative


// static	char	*check_input(char *input)
// {
// 	int		x;
// 	char	*number;

// 	x = 0;
// 	while ((input[x] >= 9 && input[x] <= 13) || input[x] == 32)
// 		x++;
// 	if (input[x] == '+')
// 		x++;
// 	else if (input[x] == '-')
// 		error_mes_exit("		[TRAFFIC LIGHT]ERROR[TRAFFIC LIGHT]\n[NO ENTRY]INPUT CANT BE NEGATIVE\n[NO ENTRY]");
// 	if (!(input[x] >= '0' && input[x] <= '9'))
// 		error_mes_exit("		[TRAFFIC LIGHT]ERROR[TRAFFIC LIGHT]\n[NO ENTRY]INPUT MUST BE NUMBERS\n[NO ENTRY]");
// 	number = input + x;
// 	x = 0;
// 	while (number[x] >= '0' && number[x] <= '9')
// 		x++;
// 	if (x > 10)
// 		error_mes_exit("		[TRAFFIC LIGHT]ERROR[TRAFFIC LIGHT]\n[NO ENTRY]THE INPUT IS BIGGER THAN INT_MAX[NO ENTRY]");
// 	return (number);
// }

// // static long	atoi_v2(char *s)
// // {
// // 	int		x;
// // 	long	result;

// // 	s = check_input(s);
// // 	result = 0;
// // 	x = 0;  // Add initialization
// // 	while (s[x] >= '0' && s[x] <= '9')
// // 	{
// // 		result = result * 10 + (s[x] - '0');
// // 		x++;
// // 	}
// // 	if (result > INT_MAX)
// // 		error_mes_exit("		[TRAFFIC LIGHT]ERROR[TRAFFIC LIGHT]\n[NO ENTRY]INT_MAX IS THE LIMIT[NO ENTRY]");
// // 	return (result);
// // }


// static long	atoi_v2(char *s)
// {
// 	int		x;
// 	long	result;

// 	s = check_input(s);
// 	result = 0;
// 	x = 0;
// 	while (s[x] >= '0' && s[x] <= '9')
// 	{
// 		result = result * 10 + (s[x] - '0');
// 		if (result > INT_MAX)
// 			error_mes_exit("ERROR: Value exceeds INT_MAX\n");
// 		x++;
// 	}
// 	return (result);
// }

///////////////./philo xxx //// xxx //// xxx  //// xxx //// [x]/////////////a philosopher is a struct and forks are mutex

// void	input_pars(t_args *input, char **av)
// {
// 	input->philo_nbr = atoi_v2(av[1]);
// 	//in miliseconds
// 	input->time_to_die = atoi_v2(av[2]) * 1000;
// 	input->time_to_eat = atoi_v2(av[3]) * 1000;
// 	input->time_to_sleep = atoi_v2(av[4]) * 1000;

// 	if (input->time_to_die < 60000 || input->time_to_eat < 60000 || input->time_to_sleep < 60000)
// 		error_mes_exit("		[TRAFFIC LIGHT]ERROR[TRAFFIC LIGHT]\n[NO ENTRY]TIME SHOULD BE MORE THAN 60 MILLI.SE.[NO ENTRY]");
// 	if (av[5])
// 		input->meals_limit = atoi_v2(av[5]);
// 	else
// 		input->meals_limit = 0;
// }

// void	input_pars(int ac, char **av, t_args *input)
// {
// 	input->philo_nbr = atoi_v2(av[1]);
// 	if (input->philo_nbr <= 0)
// 		error_mes_exit("ERROR: Need at least 1 philosopher\n");
// 	input->time_to_die = atoi_v2(av[2]) * 1000; // Convert to microseconds
// 	input->time_to_eat = atoi_v2(av[3]) * 1000; // Convert to microseconds
// 	input->time_to_sleep = atoi_v2(av[4]) * 1000; // Convert to microseconds
//     // Check for minimum time values
// 	if (input->time_to_die < 60000 || input->time_to_eat < 60000 || input->time_to_sleep < 60000)
// 		error_mes_exit("ERROR: Time values must be at least 60ms\n");
//     // Optional parameter: number of times each philosopher must eat
// 	if (ac == 6)
// 	{
// 		input->meals_limit = atoi_v2(av[5]);
// 		if (input->meals_limit <= 0)
// 			error_mes_exit("ERROR: Meals limit must be positive\n");
// 	}
// 	else
// 		input->meals_limit = -1; // No limit
// }


int check_input(const char *str)
{
    // First check if str is NULL before trying to access it
    if (!str)
        return (1);

    if (*str == '+')
        str++;
    while (*str)
    {
        if (!(*str >= '0' && *str <= '9')) // Note the quotes around digits
            return (1);
        str++;
    }
    return (0);
}

int	atoi_v2(const char *str)
{
	unsigned long long	res;

	res = 0;
	if (check_input(str))
		return (-1);
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if (res > INT_MAX)
			return (-1);
		str++;
	}
	return (res);
}

// int	input_pars(int ac, char **av, t_args *input)
// {
// 	// First check if we have the correct number of arguments
// 	if (ac < 5 || ac > 6)
// 	{
// 		printf("Usage: ./philo <number_of_philosophers> <time_to_die> ");
// 		printf("<time_to_eat> <time_to_sleep> ");
// 		printf("[number_of_times_each_philosopher_must_eat]\n");
// 		return (1);
// 	}

// 	input->philo_nbr = atoi_v2(av[1]);
// 	input->time_to_die = atoi_v2(av[2]);
// 	input->time_to_eat = atoi_v2(av[3]);
// 	input->time_to_sleep = atoi_v2(av[4]);
// 	if (ac == 6)
// 		input->meals_limit = atoi_v2(av[5]);
// 	else
// 		input->meals_limit = -1;
// 	if (input->philo_nbr <= 0 || input->philo_nbr > 200 || input->time_to_die <= 0 || input->time_to_eat <= 0 || input->time_to_sleep <= 0 || (ac == 6 && input->meals_limit <= 0))
// 	{
// 		printf("Invalid arguments\n");
// 		return (1);
// 	}
// 	return (0);
// }

int	input_pars(int ac, char **av, t_args *input)
{
	// First check if we have the correct number of arguments
	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo <number_of_philosophers> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}

	input->philo_nbr = atoi_v2(av[1]);
	input->time_to_die = atoi_v2(av[2]);
	input->time_to_eat = atoi_v2(av[3]);
	input->time_to_sleep = atoi_v2(av[4]);
	if (ac == 6)
		input->meals_limit = atoi_v2(av[5]);
	else
		input->meals_limit = -1;

	// Remove the excessive restrictions - just check if values are positive
	if (input->philo_nbr <= 0 || input->philo_nbr > 200 ||
	    input->time_to_die <= 0 || input->time_to_eat <= 0 ||
	    input->time_to_sleep <= 0 || (ac == 6 && input->meals_limit <= 0))
	{
		printf("Invalid arguments\n");
		return (1);
	}
	return (0);
}
