#include "philo.h"

void *ph_routine(void *philo)
{
    t_philo ph;
    int     have_forks;
    int     is_dead;

    ph = *(t_philo *) philo;
    have_forks = 0;
    is_dead = 0;
    while (!is_dead)
    {
        pthread_mutex_lock(ph.mutex);
        if (*(ph.fork_left) == AVAILABLE && *(ph.fork_right) == AVAILABLE)
        {
            *(ph.fork_left) = UNAVAILABLE;
            *(ph.fork_right) = UNAVAILABLE;
            have_forks = 1;
            printf("time %i has taken a fork -left-\n", ph.ph_number);
            printf("time %i has taken a fork -right-\n", ph.ph_number);
        }
        pthread_mutex_unlock(ph.mutex);
        if (have_forks)
        {
            printf("time %i is eating\n", ph.ph_number);
            *(ph.fork_left) = AVAILABLE;
            *(ph.fork_right) = AVAILABLE;
            printf("time %i is sleeping\n", ph.ph_number);
            printf("time %i is thinking\n", ph.ph_number);
            printf("time %i died\n", ph.ph_number);
            is_dead = 1;
        }
    }
    printf("fim da tread\n");

}