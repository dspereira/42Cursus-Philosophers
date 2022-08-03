/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theads.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:28:36 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/03 17:03:30 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_threads(t_philo *ph, int n);

void	create_threads(t_philo *ph)
{
	int	err;
	int	n_ph;
	int	i;

	n_ph = ph[0].stg.number_of_ph;
	i = 0;
	while (i < n_ph)
	{
		err = pthread_create(&(ph[i].thread), NULL, &ph_routine, &ph[i]);
		if (err)
		{
			wait_threads(ph, i);
			destroy_all_mutex(ph);
		}
		thread_error(err, PTHREAD_ERR);
		i++;
	}
}

void	wait_all_threads(t_philo *ph)
{
	int	n_ph;
	int	i;

	n_ph = ph[0].stg.number_of_ph;
	i = 0;
	while (i < n_ph)
	{
		pthread_join(ph[i].thread, NULL);
		i++;
	}
}

static void	wait_threads(t_philo *ph, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(ph[i].thread, NULL);
		i++;
	}
}
