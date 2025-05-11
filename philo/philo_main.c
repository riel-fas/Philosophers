// #include "philosophers.h"

// int main(int ac, char **av)
// {
//     t_data  data;

//     if (ac < 5 || ac > 6)
//     {
//         printf("Usage: %s number_of_philosophers time_to_die ", av[0]);
//         printf("time_to_eat time_to_sleep [number_of_meals]\n");
//         return (1);
//     }
//     if (init_data(&data, ac, av))
//         return (1);
//     if (init_philos(&data))
//     {
//         cleanup(&data);
//         return (1);
//     }
//     monitor(&data);
//     cleanup(&data);
//     return (0);
// }

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_pinfo		*pinfo;
	t_philo		*philos;
	pthread_t	monitor_thread;

	if (!philo_init(&pinfo, ac - 1, av + 1))
		return (EXIT_FAILURE);
	philos = create_philos(pinfo);
	if (!philos)
		return (EXIT_FAILURE);
	assign_forks(philos, pinfo);
	start_routine(philos, pinfo);
	pthread_create(&monitor_thread, NULL, monitor, philos);
	join_threads(philos, pinfo);
	pthread_join(monitor_thread, NULL);
	clear_mutexes(philos);
	free_resources(philos, pinfo);
	return (EXIT_SUCCESS);
}
