#include "philosophers.h"

long long	get_last_meal(t_shared_data *sd)
{
	long long	last_meal;

	pthread_mutex_lock(&sd->last_meal_mutex);
	last_meal = sd->last_meal;
	pthread_mutex_unlock(&sd->last_meal_mutex);
	return (last_meal);
}

int	get_died(t_pinfo *pinfo)
{
	int	boolean;

	pthread_mutex_lock(pinfo->died_mutex);
	boolean = pinfo->died;
	pthread_mutex_unlock(pinfo->died_mutex);
	return (boolean);
}

int	get_meals(t_shared_data *sd)
{
	int	meals;

	pthread_mutex_lock(&sd->meals_mutex);
	meals = sd->meals;
	pthread_mutex_unlock(&sd->meals_mutex);
	return (meals);
}

int	get_full(t_pinfo *pinfo)
{
	int	is_full;

	pthread_mutex_lock(pinfo->full_mutex);
	is_full = pinfo->full;
	pthread_mutex_unlock(pinfo->full_mutex);
	return (is_full);
}
