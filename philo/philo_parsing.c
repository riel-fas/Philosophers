/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:33:41 by riel-fas          #+#    #+#             */
/*   Updated: 2025/06/05 18:01:26 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	}
	return (number * sign);
}

int	check_args(t_philoinfo *pinfo, char *num_eats)
{
	return (pinfo->philo_number <= 0 || pinfo->time_to_die < 60
		|| pinfo->time_to_eat < 60 || pinfo->time_to_sleep < 60
		|| (num_eats && pinfo->meal_limit <= 0));
}

int	check_errors(t_philoinfo *pinfo, char *num_eats, int error_found)
{
	if (check_args(pinfo, num_eats) || error_found)
	{
		free(pinfo);
		return (0);
	}
	return (1);
}
