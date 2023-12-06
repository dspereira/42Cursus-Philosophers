/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:47:21 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/03 15:23:20 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutex(t_forks *forks, int n_forks, pthread_mutex_t *mutex);

void	init_mutex(t_forks *forks, int n_forks, pthread_mutex_t *mutex)
{
	int	i;
	int	err;

	err = pthread_mutex_init(mutex, NULL);
	thread_error(err, MUTEX_ERR);
	i = 0;
	while (i < n_forks)
	{
		err = pthread_mutex_init(&forks[i].mutex, NULL);
		if (err)
			destroy_mutex(forks, i, mutex);
		thread_error(err, MUTEX_ERR);
		i++;
	}
}

void	destroy_all_mutex(t_philo *ph)
{
	t_forks	*forks;
	int		n_ph;
	int		i;

	forks = ph[0].forks;
	n_ph = ph[0].stg.number_of_ph;
	i = 0;
	while (i < n_ph)
	{
		pthread_mutex_destroy(&forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(ph[0].mutex);
}

static void	destroy_mutex(t_forks *forks, int n_forks, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < n_forks)
	{
		pthread_mutex_destroy(&forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(mutex);
}
