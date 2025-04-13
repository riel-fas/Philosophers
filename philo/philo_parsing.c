/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 03:05:34 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/13 05:21:27 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_input(const char *str)
{
	if (!str)
		return (1);
	if (*str == '+')
		str++;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
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

int	input_pars(int ac, char **av, t_args *input)
{
	input->philo_nbr = atoi_v2(av[1]);
	input->time_to_die = atoi_v2(av[2]);
	input->time_to_eat = atoi_v2(av[3]);
	input->time_to_sleep = atoi_v2(av[4]);

	if (input->time_to_die < 60 || input->time_to_eat < 60 || input->time_to_sleep < 60)
		error_mes_exit("⛔️ERROR: Time values must be at least 60ms⛔️");

	if (ac == 6)
		input->meals_limit = atoi_v2(av[5]);
	else
		input->meals_limit = 0;

	if (input->philo_nbr <= 0 || input->philo_nbr > 200 ||
	    input->time_to_die <= 0 || input->time_to_eat <= 0 ||
	    input->time_to_sleep <= 0 || (ac == 6 && input->meals_limit <= 0))
	{
		printf("Invalid arguments\n⛔️");
		return (1);
	}
	return (0);
}
