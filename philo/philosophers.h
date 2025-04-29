/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 03:05:34 by riel-fas          #+#    #+#             */
/*   Updated: 2025/04/29 09:02:56 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_args t_args;

typedef struct s_philosopher
{
	int				philo_id;
	int				meal_count;
	int				full;
	long			last_meal_time;
	pthread_t		thread_id;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_args			*input;
}	t_philosopher;

typedef struct s_args
{
	int				philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_limit;
	long			start_time;
	bool			simulation_off;
	t_philosopher	*philosophers;
	t_fork			*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	status_mutex;
}	t_args;

/* philo_main.c */
int		main(int ac, char **av);

/* philo_plus.c */
void	error_mes_exit(char *error);
long	get_current_time(void);
void	print_status(t_philosopher *philo, char *status);
// void	precise_sleep(long milliseconds);
void	precise_sleep(long milliseconds, t_args *input);


/* philo_parsing.c */
int		check_input(const char *str);
int		atoi_v2(const char *str);
int		input_pars(int ac, char **av, t_args *input);

/* philo_action.c */
void	init_forks(t_args *input);
void	init_philosophers(t_args *input);
void	create_threads(t_args *input);
void	philo_act(t_args *input);
void	monitor_philosophers(t_args *input);

// void *monitor_philosophers(void *arg);

void	cleanup_resources(t_args *input);

/* philo_routine.c */
void	pick_forks(t_philosopher *philo);
void	eat(t_philosopher *philo);
void	release_forks(t_philosopher *philo);
void	*philosopher_routine(void *arg);

void	init_resources(t_args *input);
void	init_mutexes(t_args *input);
void	start_simulation(t_args *input);



#endif
