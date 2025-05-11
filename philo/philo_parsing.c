/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:33:41 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/11 15:36:03 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philosophers.h"

// int	check_input(const char *str)
// {
// 	if (!str)
// 		return (1);
// 	if (*str == '+')
// 		str++;
// 	while (*str)
// 	{
// 		if (!(*str >= '0' && *str <= '9'))
// 			return (1);
// 		str++;
// 	}
// 	return (0);
// }

// int	atoi_v2(const char *str)
// {
// 	unsigned long long	res;

// 	res = 0;
// 	if (check_input(str))
// 		return (-1);
// 	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
// 		|| *str == '\f' || *str == '\r')
// 		str++;
// 	if (*str == '+')
// 		str++;
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		res = res * 10 + (*str - '0');
// 		if (res > INT_MAX)
// 			return (-1);
// 		str++;
// 	}
// 	return (res);
// }

// int	input_pars(int ac, char **av, t_args *input)
// {
// 	input->philo_nbr = atoi_v2(av[1]);
// 	input->time_to_die = atoi_v2(av[2]);
// 	input->time_to_eat = atoi_v2(av[3]);
// 	input->time_to_sleep = atoi_v2(av[4]);

// 	if (input->time_to_die < 60 || input->time_to_eat < 60 || input->time_to_sleep < 60)
// 		error_mes_exit("⛔️ERROR: Time values must be at least 60ms⛔️");

// 	if (ac == 6)
// 		input->meals_limit = atoi_v2(av[5]);
// 	else
// 		input->meals_limit = 0;

// 	if (input->philo_nbr <= 0 || input->philo_nbr > 200 ||
// 	    input->time_to_die <= 0 || input->time_to_eat <= 0 ||
// 	    input->time_to_sleep <= 0 || (ac == 6 && input->meals_limit <= 0))
// 	{
// 		printf("Invalid arguments\n⛔️");
// 		return (1);
// 	}
// 	return (0);
// }


#include "philosophers.h"

static int	skipspaces(const char *str)
{
	size_t	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

static int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_atoi(const char *str, int *error_found)
{
	size_t	i;
	int		sign;
	long	number;

	number = 0;
	sign = 1;
	i = skipspaces(str);
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			*error_found = 1;
			return (0);
		}
		number = (number * 10) + str[i++] - 48;
		if (number > INT_MAX)
			*error_found = 1;
	}
	return (number * sign);
}
