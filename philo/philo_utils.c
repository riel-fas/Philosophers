#include "philosophers.h"

long get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long elapsed_time(long start)
{
    return (get_time() - start);
}

void print_status(t_philo *philo, t_status status)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->sim_stop)
    {
        printf("%ld %d ", elapsed_time(philo->data->start_time), philo->id);
        if (status == FORK_TAKEN)
            printf("has taken a fork\n");
        else if (status == EATING)
            printf("is eating\n");
        else if (status == SLEEPING)
            printf("is sleeping\n");
        else if (status == THINKING)
            printf("is thinking\n");
        else if (status == DIED)
            printf("died\n");
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void precise_sleep(long ms, t_data *data)
{
    long start;

    start = get_time();
    while ((get_time() - start) < ms)
    {
        pthread_mutex_lock(&data->death_mutex);
        if (data->sim_stop)
        {
            pthread_mutex_unlock(&data->death_mutex);
            break;
        }
        pthread_mutex_unlock(&data->death_mutex);
        usleep(100);
    }
}

int ft_atoi(const char *str)
{
    long result;
    int sign;

    result = 0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        if (result > INT_MAX)
            return (sign == 1 ? INT_MAX : INT_MIN);
        str++;
    }
    return (result * sign);
}

void error_exit(char *msg)
{
    printf("Error: %s\n", msg);
    exit(1);
}
