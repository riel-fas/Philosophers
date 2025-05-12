/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 03:05:34 by riel-fas          #+#    #+#             */
/*   Updated: 2025/05/12 15:38:55 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_stats
{
	FORK_TAKEN,
	EAT,
	SLEEP,
	THINK,
	DIED
}	t_stats;

typedef struct s_philoinfo
{
	pthread_mutex_t		*print_mutex;
	pthread_mutex_t		*died_mutex;
	pthread_mutex_t		*full_mutex;
	int					died;
	int					full;
	long				start_time;
	int					philo_number;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meal_limit;
}	t_philoinfo;

typedef struct s_data
{
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		meals_mutex;
	unsigned long		last_meal;
	int					meals;
}	t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	int					is_full;
	t_data				sd;
	t_philoinfo			*pinfo;
}	t_philo;

//philo_getters.c
long long		get_last_meal(t_data *sd);
int				get_died(t_philoinfo *pinfo);
int				get_meals(t_data *sd);
int				get_full(t_philoinfo *pinfo);

//philo_setters.c
void			set_last_meal(t_data *sd);
void			set_died(t_philoinfo *pinfo, int boolean);
void			increment_meals(t_data *sd);
void			set_full(t_philoinfo *pinfo, int is_full);

//philo_init.c
int				mutexes_init(t_philoinfo *info);
int				check_params(t_philoinfo *info, char *num_eats);
int				check_errors(t_philoinfo *info,
					char *num_eats, int error_found);
int				philo_init(t_philoinfo **info, int count, char **data);

//philo_manager.c
t_philo			*create_philos(t_philoinfo *info);
void			forks_assignement(t_philo *philos, t_philoinfo *info);
void			routine_start(t_philo *philos, t_philoinfo *info);
void			join_threads(t_philo *philos, t_philoinfo *pinfo);

//philo_monitoring.c
int				death_check(t_philo *philos);
int				meals_check(t_philo *philos, int *full);
void			*monitor(void *param);

//philo_parsing.c
int				check_params(t_philoinfo *pinfo, char *num_eats);
int				check_errors(t_philoinfo *pinfo, char *num_eats,
					int error_found);
int				ft_atoi(const char *str, int *error_found);
int				check_args(t_philoinfo *pinfo, char *num_eats);

//philo_print.c
void			safe_print(t_philo *philo, t_stats status);

//philo_routine.c
int				ph_eat(t_philo *philo);
int				ph_sleep(t_philo *philo);
void			ph_think(t_philo *philo);
void			*routine(void *param);

//philo_time.c
long long		get_current_time(void);
unsigned long	program_time(long start_time);
void			precise_sleep(unsigned long ms, t_philoinfo *pinfo);

//philo_utils.c
void			clear_mutexes(t_philo *philos);
void			*free_philos(t_philo *philos, int size);
void			free_resources(t_philo *philos, t_philoinfo *pinfo);
void			unlock_mutexes(t_philo *philos);

#endif
