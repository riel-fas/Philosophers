#include "philosophers.h"

void	error_mes_exit(char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

// Get current time in milliseconds
long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// Print philosopher status with timestamp
void	print_status(t_philosopher *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->input->print_mutex);
	if (philo->input->simulation_off)
	{
		pthread_mutex_unlock(&philo->input->print_mutex);
		return;
	}
	timestamp = get_current_time() - philo->input->start_time;
	printf("%ld %d %s\n", timestamp, philo->philo_id, status);
	pthread_mutex_unlock(&philo->input->print_mutex);
}

// More precise sleep function
void	precise_sleep(long milliseconds)
{
	long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < milliseconds)
		usleep(100); // Sleep in small intervals for more precision
}
