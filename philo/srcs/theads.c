/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theads.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:28:36 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/02 12:29:30 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void create_threads(t_philo *ph, int n)
{
    int i;
    int err;

    i = 0;
    while (i < n)
    {
        err = pthread_create(&(ph[i].thread), NULL, &ph_routine, &ph[i]);
        if (err && i)
        {
            wait_threads(ph, i);
            //destroy mutex
        }
        thread_error(err, PTHREAD_CREATE);
        i++;
    }
}

void wait_threads(t_philo *ph, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        pthread_join(ph[i].thread, NULL);
        i++;
    }
}
