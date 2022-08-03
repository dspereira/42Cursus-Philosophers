/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:47:21 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/03 10:20:18 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_mutex(t_forks *forks, int n_forks, pthread_mutex_t *mutex)
{
    int i;
    int err;

    err = pthread_mutex_init(mutex, NULL);
    thread_error(err, MUTEX_INIT);
    i = 0;
    while (i < n_forks)
    {
        err = pthread_mutex_init(&forks[i].mutex, NULL);
        if (err)
            destroy_mutex(forks, i, mutex);
        thread_error(err, MUTEX_INIT);
        i++;
    }
}

void destroy_mutex(t_forks *forks, int n_forks, pthread_mutex_t *mutex)
{
    int i;

    i = 0;
    while (i < n_forks)
    {
        pthread_mutex_destroy(&forks[i].mutex);
        i++;
    }
    pthread_mutex_destroy(mutex);
}