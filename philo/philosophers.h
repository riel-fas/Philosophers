#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef enum e_status {
    FORK_TAKEN,
    EATING,
    SLEEPING,
    THINKING,
    DIED
} t_status;

typedef struct s_fork {
    pthread_mutex_t mutex;
    int             id;
} t_fork;

typedef struct s_philo {
    int             id;
    pthread_t       thread;
    struct s_data   *data;
    t_fork          *left_fork;
    t_fork          *right_fork;
    long            last_meal;
    int             meal_count;
    bool            full;
    pthread_mutex_t meal_mutex;
    pthread_mutex_t last_meal_mutex;
} t_philo;

typedef struct s_data {
    int             philo_count;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    int             meal_limit;
    long            start_time;
    bool            sim_stop;
    t_philo         *philos;
    t_fork          *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    pthread_mutex_t full_mutex;
} t_data;

/* Core Functions */
int     init_data(t_data *data, int ac, char **av);
int     init_philos(t_data *data);
void    cleanup(t_data *data);
void    monitor(t_data *data);
void    *routine(void *arg);

/* Utils */
long    get_time(void);
long    elapsed_time(long start);
void    print_status(t_philo *philo, t_status status);
void    precise_sleep(long ms, t_data *data);
int     ft_atoi(const char *str);
void    error_exit(char *msg);

#endif
