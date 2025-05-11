#include "philosophers.h"

int	init_mutexes(t_pinfo *pinfo)
{
	pinfo->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!pinfo->print_mutex)
		return (0);
	pinfo->died_mutex = malloc(sizeof(pthread_mutex_t));
	if (!pinfo->died_mutex)
	{
		free(pinfo->print_mutex);
		return (0);
	}
	pinfo->full_mutex = malloc(sizeof(pthread_mutex_t));
	if (!pinfo->full_mutex)
	{
		free(pinfo->print_mutex);
		free(pinfo->died_mutex);
		return (0);
	}
	pthread_mutex_init(pinfo->print_mutex, NULL);
	pthread_mutex_init(pinfo->died_mutex, NULL);
	pthread_mutex_init(pinfo->full_mutex, NULL);
	return (1);
}

int	check_params(t_pinfo *pinfo, char *num_eats)
{
	return (pinfo->pnumber <= 0 || pinfo->die_time <= 0 || pinfo->eat_time <= 0
		|| pinfo->sleep_time <= 0 || (num_eats && pinfo->num_eats <= 0));
}

int	check_errors(t_pinfo *pinfo, char *num_eats, int error_found)
{
	if (check_params(pinfo, num_eats) || error_found)
	{
		free(pinfo);
		return (0);
	}
	return (1);
}

int	philo_init(t_pinfo **pinfo, int count, char **data)
{
	int	error_found;

	error_found = 0;
	if (count < 4 || count > 5)
		return (0);
	*pinfo = malloc(sizeof(t_pinfo));
	if (!*pinfo)
		return (0);
	**pinfo = (t_pinfo){0};
	(*pinfo)->pnumber = ft_atoi(data[0], &error_found);
	(*pinfo)->die_time = ft_atoi(data[1], &error_found);
	(*pinfo)->eat_time = ft_atoi(data[2], &error_found);
	(*pinfo)->sleep_time = ft_atoi(data[3], &error_found);
	if (data[4])
		(*pinfo)->num_eats = ft_atoi(data[4], &error_found);
	else
		(*pinfo)->num_eats = -1;
	if (!check_errors(*pinfo, data[4], error_found))
		return (0);
	return (init_mutexes((*pinfo)));
}
