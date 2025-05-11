// #include "philosophers.h"

// static int check_death(t_data *data, int i)
// {
//     long current;
//     long last_meal;

//     pthread_mutex_lock(&data->philos[i].last_meal_mutex);
//     current = get_time();
//     last_meal = data->philos[i].last_meal;
//     pthread_mutex_unlock(&data->philos[i].last_meal_mutex);

//     if ((current - last_meal) > data->time_to_die)
//     {
//         pthread_mutex_lock(&data->death_mutex);
//         data->sim_stop = true;
//         pthread_mutex_unlock(&data->death_mutex);
//         print_status(&data->philos[i], DIED);
//         return (1);
//     }
//     return (0);
// }

// static int check_full(t_data *data)
// {
//     int i;
//     int full_count;

//     full_count = 0;
//     i = -1;
//     while (++i < data->philo_count)
//     {
//         pthread_mutex_lock(&data->philos[i].meal_mutex);
//         if (data->philos[i].full)
//             full_count++;
//         pthread_mutex_unlock(&data->philos[i].meal_mutex);
//     }
//     if (full_count == data->philo_count)
//     {
//         pthread_mutex_lock(&data->full_mutex);
//         data->sim_stop = true;
//         pthread_mutex_unlock(&data->full_mutex);
//         return (1);
//     }
//     return (0);
// }

// void monitor(t_data *data)
// {
//     int i;

//     while (1)
//     {
//         i = -1;
//         while (++i < data->philo_count)
//         {
//             if (check_death(data, i))
//                 return;
//         }
//         if (data->meal_limit > 0 && check_full(data))
//             return;
//         usleep(1000);
//     }
// }

// void cleanup(t_data *data)
// {
//     int i;

//     i = -1;
//     while (++i < data->philo_count)
//         pthread_join(data->philos[i].thread, NULL);

//     i = -1;
//     while (++i < data->philo_count)
//     {
//         pthread_mutex_destroy(&data->philos[i].meal_mutex);
//         pthread_mutex_destroy(&data->philos[i].last_meal_mutex);
//         pthread_mutex_destroy(&data->forks[i].mutex);
//     }

//     pthread_mutex_destroy(&data->print_mutex);
//     pthread_mutex_destroy(&data->death_mutex);
//     pthread_mutex_destroy(&data->full_mutex);

//     free(data->philos);
//     free(data->forks);
// }


#include "philosophers.h"

int	check_death(t_philo *philos)
{
	int		i;
	t_pinfo	*pinfo;

	i = 0;
	pinfo = philos[0].pinfo;
	while (i < pinfo->pnumber)
	{
		if (timestamp() - get_last_meal(&philos[i].sd) >= pinfo->die_time)
		{
			set_died(pinfo, 1);
			safe_print(&philos[i], DIED);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_meals(t_philo *philos, int *full)
{
	int		i;
	t_pinfo	*pinfo;

	i = 0;
	pinfo = philos[0].pinfo;
	if (pinfo->num_eats == -1)
		return (1);
	while (i < pinfo->pnumber)
	{
		if (get_meals(&philos[i].sd) >= pinfo->num_eats && !philos[i].is_full)
		{
			philos[i].is_full = 1;
			(*full)++;
		}
		if ((*full) >= pinfo->pnumber)
		{
			set_full(pinfo, 1);
			return (0);
		}
		i++;
	}
	return (1);
}

void	*monitor(void *param)
{
	t_philo	*philos;
	t_pinfo	*pinfo;
	int		full;

	full = 0;
	philos = (t_philo *)param;
	pinfo = philos[0].pinfo;
	while (!get_died(pinfo) && check_meals(philos, &full))
	{
		if (!check_death(philos))
			break;
		usleep(1000);
	}
	return (NULL);
}
