// #include "philosophers.h"

// static void eat(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->left_fork->mutex);
//     print_status(philo, FORK_TAKEN);

//     // Check for single philosopher case
//     if (philo->data->philo_count == 1)
//     {
//         precise_sleep(philo->data->time_to_die, philo->data);
//         pthread_mutex_unlock(&philo->left_fork->mutex);
//         return;
//     }

//     pthread_mutex_lock(&philo->right_fork->mutex);
//     print_status(philo, FORK_TAKEN);

//     print_status(philo, EATING);
//     pthread_mutex_lock(&philo->last_meal_mutex);
//     philo->last_meal = get_time();
//     pthread_mutex_unlock(&philo->last_meal_mutex);

//     precise_sleep(philo->data->time_to_eat, philo->data);

//     pthread_mutex_lock(&philo->meal_mutex);
//     philo->meal_count++;
//     if (philo->data->meal_limit > 0 &&
//         philo->meal_count >= philo->data->meal_limit)
//         philo->full = true;
//     pthread_mutex_unlock(&philo->meal_mutex);

//     pthread_mutex_unlock(&philo->left_fork->mutex);
//     pthread_mutex_unlock(&philo->right_fork->mutex);
// }

// void *routine(void *arg)
// {
//     t_philo *philo = (t_philo *)arg;

//     // Stagger the philosophers to reduce contention
//     if (philo->id % 2 == 0)
//         usleep(1000);

//     while (1)
//     {
//         pthread_mutex_lock(&philo->data->death_mutex);
//         if (philo->data->sim_stop)
//         {
//             pthread_mutex_unlock(&philo->data->death_mutex);
//             break;
//         }
//         pthread_mutex_unlock(&philo->data->death_mutex);

//         eat(philo);

//         // Check again if simulation should stop
//         pthread_mutex_lock(&philo->data->death_mutex);
//         if (philo->data->sim_stop)
//         {
//             pthread_mutex_unlock(&philo->data->death_mutex);
//             break;
//         }
//         pthread_mutex_unlock(&philo->data->death_mutex);

//         print_status(philo, SLEEPING);
//         precise_sleep(philo->data->time_to_sleep, philo->data);
//         print_status(philo, THINKING);
//     }
//     return (NULL);
// }


#include "philosophers.h"

int	eat(t_philo *philo)
{
	t_pinfo	*pinfo;

	pinfo = philo->pinfo;
	pthread_mutex_lock(philo->l_fork);
	safe_print(philo, FORK_TAKEN);
	if (pinfo->pnumber == 1)
	{
		await(pinfo->die_time, pinfo);
		pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	pthread_mutex_lock(philo->r_fork);
	safe_print(philo, FORK_TAKEN);
	if (get_full(pinfo) || get_died(pinfo))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	safe_print(philo, EAT);
	set_last_meal(&philo->sd);
	await(pinfo->eat_time, pinfo);
	increment_meals(&philo->sd);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (1);
}

int	t_sleep(t_philo *philo)
{
	t_pinfo	*pinfo;

	pinfo = philo->pinfo;
	if (get_full(pinfo) || get_died(pinfo))
		return (0);
	safe_print(philo, SLEEP);
	await(pinfo->sleep_time, pinfo);
	return (1);
}

void	think(t_philo *philo)
{
	safe_print(philo, THINK);
}

void	*routine(void *param)
{
	t_philo	*philo;
	t_pinfo	*pinfo;

	philo = (t_philo *)param;
	pinfo = philo->pinfo;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!get_died(pinfo) && !get_full(pinfo))
	{
		think(philo);
		if (!eat(philo))
			break ;
		if (!t_sleep(philo))
			break ;
	}
	return (NULL);
}
