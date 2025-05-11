#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef enum e_status
{
	FORK_TAKEN,
	EAT,
	SLEEP,
	THINK,
	DIED
}					t_status;

typedef struct s_pinfo
{
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*died_mutex;
	pthread_mutex_t	*full_mutex;
	int				died;
	int				full;
	long			start_time;
	int				pnumber;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				num_eats;
}					t_pinfo;

typedef struct s_shared_data
{
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	meals_mutex;
	unsigned long	last_meal;
	int				meals;

}					t_shared_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				is_full;
	t_shared_data	sd;
	t_pinfo			*pinfo;
}					t_philo;

// # All Functions with Semicolons

int main(int ac, char **av);
int init_mutexes(t_pinfo *pinfo);
int check_params(t_pinfo *pinfo, char *num_eats);
int check_errors(t_pinfo *pinfo, char *num_eats, int error_found);
int philo_init(t_pinfo **pinfo, int count, char **data);
t_philo *create_philos(t_pinfo *pinfo);
void assign_forks(t_philo *philos, t_pinfo *pinfo);
void start_routine(t_philo *philos, t_pinfo *pinfo);
long long timestamp(void);
unsigned long program_time(long start_time);
void await(unsigned long ms, t_pinfo *pinfo);
void join_threads(t_philo *philos, t_pinfo *pinfo);
long long get_last_meal(t_shared_data *sd);
int get_died(t_pinfo *pinfo);
int get_meals(t_shared_data *sd);
int get_full(t_pinfo *pinfo);
void set_last_meal(t_shared_data *sd);
void set_died(t_pinfo *pinfo, int boolean);
void increment_meals(t_shared_data *sd);
void set_full(t_pinfo *pinfo, int is_full);
int eat(t_philo *philo);
int t_sleep(t_philo *philo);
void think(t_philo *philo);
void *routine(void *param);
int check_death(t_philo *philos);
int check_meals(t_philo *philos, int *full);
void *monitor(void *param);
void safe_print(t_philo *philo, t_status status);
void clear_mutexes(t_philo *philos);
void *free_philos(t_philo *philos, int size);
void free_resources(t_philo *philos, t_pinfo *pinfo);
void unlock_mutexes(t_philo *philos);
int ft_atoi(const char *str, int *error_found);

#endif
