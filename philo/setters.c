#include "philosophers.h"

void	set_last_meal(t_shared_data *sd)
{
	pthread_mutex_lock(&sd->last_meal_mutex);
	sd->last_meal = timestamp();
	pthread_mutex_unlock(&sd->last_meal_mutex);
}

void	set_died(t_pinfo *pinfo, int boolean)
{
	pthread_mutex_lock(pinfo->died_mutex);
	pinfo->died = boolean;
	pthread_mutex_unlock(pinfo->died_mutex);
}

void	increment_meals(t_shared_data *sd)
{
	pthread_mutex_lock(&sd->meals_mutex);
	sd->meals++;
	pthread_mutex_unlock(&sd->meals_mutex);
}

void	set_full(t_pinfo *pinfo, int is_full)
{
	pthread_mutex_lock(pinfo->full_mutex);
	pinfo->full = is_full;
	pthread_mutex_unlock(pinfo->full_mutex);
}
