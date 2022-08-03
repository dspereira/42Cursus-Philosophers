/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:23:52 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/02 17:23:56 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	hold_fork(t_forks *fork);

int	holding_forks(t_philo *ph)
{
	int	state;

	state = HOLDING_FORKS;
	if (hold_fork(ph->fork_left))
	{
		printf("%lu %i has taken a fork\n", get_actual_time_ms(), ph->ph_number);
		ph->n_forks_hold++;
	}
	if (hold_fork(ph->fork_right))
	{
		printf("%lu %i has taken a fork\n", get_actual_time_ms(), ph->ph_number);
		ph->n_forks_hold++;
	}
	if (ph->n_forks_hold == 2)
	{
		ph->n_forks_hold = 0;
		state = EATING;
	}
	return (state);
}

void	drop_forks(t_philo ph)
{
	pthread_mutex_lock(&(ph.fork_left->mutex));
	ph.fork_left->state = AVAILABLE;
	pthread_mutex_unlock(&(ph.fork_left->mutex));
	pthread_mutex_lock(&(ph.fork_right->mutex));
	ph.fork_right->state = AVAILABLE;
	pthread_mutex_unlock(&(ph.fork_right->mutex));
}

static int	hold_fork(t_forks *fork)
{
	int	state;

	state = 0;
	if (!fork)
		return (state);
	pthread_mutex_lock(&(fork->mutex));
	if (fork->state == AVAILABLE)
	{
		fork->state = UNAVAILABLE;
		state = 1;
	}
	pthread_mutex_unlock(&(fork->mutex));
	return (state);
}

void destroy_forks_mutex(t_forks *forks, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&forks[i].mutex);
		i++;
	}
}