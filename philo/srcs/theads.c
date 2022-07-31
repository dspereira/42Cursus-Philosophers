/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theads.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:28:36 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/31 23:15:03 by dsilveri         ###   ########.fr       */
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
        pthread_error(err, PTHREAD_CREATE);
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
