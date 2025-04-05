/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 03:30:56 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/05 04:41:26 by riel-fas         ###   ########.fr       */
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
        error_mes_exit("ERROR\nINPUT CANT BE NEGATIVE\n");
    if (!(input[x] >= '0' && input[x] <= '9'))
        error_mes_exit("ERROR\nINPUT MUST BE NUMBERS\n");
    number = input + x;
    x = 0;
    while (number[x] >= '0' && number[x] <= '9')
        x++;
    if (x > 10)
        error_mes_exit("ERROR\nTHE INPUT IS BIGGER THAN INT_MAX");
    return (number);
}
// static long	handle_overflow(int sign)
// {
// 	if (sign == 1)
// 	return (LONG_MAX);
// }

static long	atoi_v2(char *s)
{
    int		x;
    long	result;
    // int		sign;
    // long	prev_result;

    s = check_input(s);
    result = 0;
    x = 0;  // Add initialization
    // sign = 1;
    while (s[x] >= '0' && s[x] <= '9')
    {
        // prev_result = result;
        result = result * 10 + (s[x] - '0');
        // if (result / 10 != prev_result)
        // 	return (handle_overflow(sign));
        x++;
    }
    if (result > INT_MAX)
        error_mes_exit("ERROR\nINT_MAX IS THE LIMIT");
    return (result);
}

///////////////./philo xxx //// xxx //// xxx  //// xxx //// [x]/////////////a philosopher is a struct and forks are mutex

void	input_pars(t_args *input, char **av)
{
	input->philo_nbr = atoi_v2(av[1]);






}
