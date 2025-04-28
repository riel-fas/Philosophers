// #include "philosophers.h"

void monitor_philosophers(t_args *input)
{
    int i;
    int all_full;
    long current_time;

    while (1)
    {
        // Check if simulation should stop
        pthread_mutex_lock(&input->status_mutex);
        if (input->simulation_off) {
            pthread_mutex_unlock(&input->status_mutex);
            break;
        }
        pthread_mutex_unlock(&input->status_mutex);

        all_full = 1;
        i = 0;
        while (i < input->philo_nbr)
        {
            // Check if philosopher died
            pthread_mutex_lock(&input->status_mutex);
            current_time = get_current_time();
            if (!input->simulation_off &&
                (current_time - input->philosophers[i].last_meal_time > input->time_to_die))
            {
                print_status(&input->philosophers[i], "died");
                input->simulation_off = 1;
                pthread_mutex_unlock(&input->status_mutex);
                return;
            }

            // Check if philosopher is full
            if (input->meals_limit > 0 && input->philosophers[i].meal_count < input->meals_limit)
                all_full = 0;
            pthread_mutex_unlock(&input->status_mutex);

            i++;
        }

        // Check if all philosophers are full
        if (input->meals_limit > 0 && all_full)
        {
            pthread_mutex_lock(&input->status_mutex);
            input->simulation_off = 1;
            pthread_mutex_unlock(&input->status_mutex);
            break;
        }

        usleep(500); // Small sleep to avoid excessive CPU usage
    }
}
