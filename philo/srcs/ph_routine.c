/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:25:31 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/20 17:43:53 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int holding_forks(t_philo ph);
void drop_forks(t_philo ph);
int is_eating(t_philo ph);

void *ph_routine(void *philo)
{
    t_philo ph;
    int     have_forks;
    int     is_dead;
    int     n_cicles;

    ph = *(t_philo *) philo;
    have_forks = 0;
    is_dead = 0;
    n_cicles = 0;
    while (!is_dead)
    {
        have_forks = holding_forks(ph);
        if (have_forks)
        {
            printf("time %i is eating\n", ph.ph_number);
            drop_forks(ph);
            printf("time %i is sleeping\n", ph.ph_number);
            printf("time %i is thinking\n", ph.ph_number);
            n_cicles++;
            if (n_cicles == ph.args.nb_times_to_eat)
                is_dead = 1;
        }
    }
}

int holding_forks(t_philo ph)
{
    unsigned long   time_ms;
    int             have_forks;

    have_forks = 0;
    pthread_mutex_lock(ph.mutex);
    if (*(ph.fork_left) == AVAILABLE && *(ph.fork_right) == AVAILABLE)
    {
        *(ph.fork_left) = UNAVAILABLE;
        *(ph.fork_right) = UNAVAILABLE;
        time_ms = get_actual_time_ms();
        printf("%lu has taken a fork\n", time_ms, ph.ph_number);
        printf("%lu has taken a fork\n", time_ms, ph.ph_number);
        have_forks = 1;
    }
    pthread_mutex_unlock(ph.mutex);
    return (have_forks);
}

void drop_forks(t_philo ph)
{
    pthread_mutex_lock(ph.mutex);
    *(ph.fork_left) = AVAILABLE;
    *(ph.fork_right) = AVAILABLE;
    pthread_mutex_unlock(ph.mutex);
}

int is_eating(t_philo ph)
{
    static unsigned long start_time = 0;
    int                  status;

    status = 0;
    if (!start_time)
    {
        start_time = get_actual_time_ms();
        printf("%lu %i is eating\n",start_time, ph.ph_number);
    }
    if (time_has_passed(start_time, ph.args.time_to_eat))
    {
        start_time = 0;
        status = 1;
    }
    return (status);
}