// #include "philosophers.h"

// void	pick_forks(t_philosopher *philo)
// {
// 	// Always pick the lower-numbered fork first to prevent deadlock
// 	if (philo->right_fork->fork_id < philo->left_fork->fork_id)
// 	{
// 		pthread_mutex_lock(&(philo->right_fork->fork_mutex));
// 		print_status(philo, "has taken a fork");
// 		pthread_mutex_lock(&(philo->left_fork->fork_mutex));
// 		print_status(philo, "has taken a fork");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&(philo->left_fork->fork_mutex));
// 		print_status(philo, "has taken a fork");
// 		pthread_mutex_lock(&(philo->right_fork->fork_mutex));
// 		print_status(philo, "has taken a fork");
// 	}
// }

// #include "philosophers.h"

// void	eat(t_philosopher *philo)
// {
// 	t_args	*input = philo->input;
// 	print_status(philo, "is eating");

// 	// Update last meal time and meal count as soon as eating starts
// 	pthread_mutex_lock(&input->status_mutex);
// 	philo->last_meal_time = get_current_time();
// 	philo->meal_count++;
// 	if (input->meals_limit > 0 && philo->meal_count >= input->meals_limit)
// 		philo->full = 1;
// 	pthread_mutex_unlock(&input->status_mutex);

// 	// Sleep for eating duration
// 	precise_sleep(input->time_to_eat, input);
// }

// // void	eat(t_philosopher *philo)
// // {
// // 	t_args	*input;

// // 	input = philo->input;
// // 	print_status(philo, "is eating");

// // 	// Update last meal time safely
// // 	pthread_mutex_lock(&input->status_mutex);
// // 	philo->last_meal_time = get_current_time();
// // 	pthread_mutex_unlock(&input->status_mutex);

// // 	// Sleep for eating duration
// // 	// precise_sleep(input->time_to_eat);
// // 	precise_sleep(input->time_to_eat, input);
// // 	// Update meal count safely
// // 	pthread_mutex_lock(&input->status_mutex);
// // 	philo->meal_count++;
// // 	if (input->meals_limit > 0 && philo->meal_count >= input->meals_limit)
// // 		philo->full = 1;
// // 	pthread_mutex_unlock(&input->status_mutex);
// // }

// void	release_forks(t_philosopher *philo)
// {
// 	pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
// 	pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
// 	print_status(philo, "is sleeping");
// 	precise_sleep(philo->input->time_to_sleep, philo->input);
// }

// void	*philosopher_routine(void *arg)
// {
// 	t_philosopher	*philo;
// 	t_args			*input;
// 	int				simulation_active;

// 	philo = (t_philosopher *)arg;
// 	input = philo->input;

// 	// Set last meal time to start time
// 	pthread_mutex_lock(&input->status_mutex);
// 	philo->last_meal_time = get_current_time();
// 	pthread_mutex_unlock(&input->status_mutex);

// 	// Handle single philosopher case
// 	if (input->philo_nbr == 1)
// 	{
// 		print_status(philo, "has taken a fork");
// 		precise_sleep(input->time_to_die, input);
// 		return (NULL);
// 	}

// 	// Stagger philosophers to prevent deadlock
// 	if (philo->philo_id % 2 == 0)
// 		precise_sleep(input->time_to_eat / 2, input);

// 	// Main philosopher loop
// 	while (1)
// 	{
// 		pthread_mutex_lock(&input->status_mutex);
// 		simulation_active = !input->simulation_off;
// 		pthread_mutex_unlock(&input->status_mutex);

// 		if (!simulation_active)
// 			break;

// 		print_status(philo, "is thinking");
// 		pick_forks(philo);

// 		pthread_mutex_lock(&input->status_mutex);
// 		simulation_active = !input->simulation_off;
// 		pthread_mutex_unlock(&input->status_mutex);

// 		if (!simulation_active)
// 		{
// 			pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
// 			pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
// 			break;
// 		}

// 		eat(philo);
// 		release_forks(philo);

// 		pthread_mutex_lock(&input->status_mutex);
// 		if (input->meals_limit > 0 && philo->meal_count >= input->meals_limit)
// 		{
// 			pthread_mutex_unlock(&input->status_mutex);
// 			break;
// 		}
// 		pthread_mutex_unlock(&input->status_mutex);
// 	}
// 	return (NULL);
// }



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
	t_args	*input = philo->input;

	// Lock status mutex before updating state
	pthread_mutex_lock(&input->status_mutex);
	philo->last_meal_time = get_current_time();
	// Only print if simulation is still active
	if (!input->simulation_off)
	{
		pthread_mutex_unlock(&input->status_mutex);
		print_status(philo, "is eating");
		// Lock again to update the meal count
		pthread_mutex_lock(&input->status_mutex);
	}

	philo->meal_count++;
	if (input->meals_limit > 0 && philo->meal_count >= input->meals_limit)
		philo->full = 1;
	pthread_mutex_unlock(&input->status_mutex);

	// Sleep for eating duration
	precise_sleep(input->time_to_eat, input);
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
	pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
	print_status(philo, "is sleeping");
	precise_sleep(philo->input->time_to_sleep, philo->input);
}

// Calculate appropriate thinking time to balance philosophers
void	think(t_philosopher *philo)
{
	long	time_to_think;
	t_args	*input;

	input = philo->input;
	print_status(philo, "is thinking");

	// If there's an odd number of philosophers, add dynamic thinking time
	// to prevent synchronized fork grabbing
	if (input->philo_nbr % 2 == 1)
	{
		time_to_think = (input->time_to_eat - input->time_to_sleep) / 2;
		if (time_to_think < 0)
			time_to_think = 0;
		precise_sleep(time_to_think, input);
	}
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
		precise_sleep(input->time_to_die, input);
		return (NULL);
	}

	// Stagger philosophers naturally by starting even ones with thinking
	if (philo->philo_id % 2 == 0)
		think(philo);

	// Main philosopher loop
	while (1)
	{
		pthread_mutex_lock(&input->status_mutex);
		simulation_active = !input->simulation_off;
		pthread_mutex_unlock(&input->status_mutex);

		if (!simulation_active)
			break;

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

		think(philo);
	}
	return (NULL);
}
