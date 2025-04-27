#include "philosophers.h"

void	pick_forks(t_philosopher *philo)
{
	// Always pick the lower-numbered fork first to prevent deadlock
	if (philo->right_fork->fork_id < philo->left_fork->fork_id)
	{
		pthread_mutex_lock(&(philo->right_fork->fork_mutex));
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->left_fork->fork_mutex));
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(philo->left_fork->fork_mutex));
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->right_fork->fork_mutex));
		print_status(philo, "has taken a fork");
	}
}

void	eat(t_philosopher *philo)
{
	t_args	*input;

	input = philo->input;
	print_status(philo, "is eating");

	// Update last meal time safely
	pthread_mutex_lock(&input->status_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&input->status_mutex);

	// Sleep for eating duration
	precise_sleep(input->time_to_eat);

	// Update meal count safely
	pthread_mutex_lock(&input->status_mutex);
	philo->meal_count++;
	if (input->meals_limit > 0 && philo->meal_count >= input->meals_limit)
		philo->full = 1;
	pthread_mutex_unlock(&input->status_mutex);
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
	pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
	print_status(philo, "is sleeping");
	precise_sleep(philo->input->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_args			*input;
	int				simulation_active;

	philo = (t_philosopher *)arg;
	input = philo->input;

	// Set last meal time to start time
	pthread_mutex_lock(&input->status_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&input->status_mutex);

	// Handle single philosopher case
	if (input->philo_nbr == 1)
	{
		print_status(philo, "has taken a fork");
		precise_sleep(input->time_to_die);
		return (NULL);
	}

	// Stagger philosophers to prevent deadlock
	if (philo->philo_id % 2 == 0)
		precise_sleep(input->time_to_eat / 2);

	// Main philosopher loop
	while (1)
	{
		pthread_mutex_lock(&input->status_mutex);
		simulation_active = !input->simulation_off;
		pthread_mutex_unlock(&input->status_mutex);

		if (!simulation_active)
			break;

		print_status(philo, "is thinking");
		pick_forks(philo);

		pthread_mutex_lock(&input->status_mutex);
		simulation_active = !input->simulation_off;
		pthread_mutex_unlock(&input->status_mutex);

		if (!simulation_active)
		{
			pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
			pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
			break;
		}

		eat(philo);
		release_forks(philo);

		pthread_mutex_lock(&input->status_mutex);
		if (input->meals_limit > 0 && philo->meal_count >= input->meals_limit)
		{
			pthread_mutex_unlock(&input->status_mutex);
			break;
		}
		pthread_mutex_unlock(&input->status_mutex);
	}
	return (NULL);
}
