/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:23:52 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/03 17:39:19 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	hold_fork(t_forks *fork, int n_ph);

t_forks	*init_forks(int n)
{
	t_forks	*forks;
	int		i;

	if (n > 0)
	{
		forks = oom_guard(malloc(n * sizeof(t_forks)));
		save_alloc_mem(forks);
		i = 0;
		while (i < n)
		{
			forks[i].state = AVAILABLE;
			i++;
		}
		return (forks);
	}
	return (NULL);
}

void	add_forks_to_ph(t_philo *ph, t_forks *forks)
{
	int	fork_index;

	ph->forks = forks;
	fork_index = ph->ph_number - 1;
	ph->fork_right = &forks[fork_index];
	if (ph->stg.number_of_ph > 1)
	{
		if (ph->ph_number == ph->stg.number_of_ph)
			ph->fork_left = &forks[0];
		else
			ph->fork_left = &forks[fork_index + 1];
	}
	else
		ph->fork_left = NULL;
}

int	holding_forks(t_philo *ph)
{
	int	state;

	state = HOLDING_FORKS;
	ph->n_forks_hold += hold_fork(ph->fork_left, ph->ph_number);
	ph->n_forks_hold += hold_fork(ph->fork_right, ph->ph_number);
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

static int	hold_fork(t_forks *fork, int n_ph)
{
	int	state;

	state = 0;
	if (!fork)
		return (state);
	pthread_mutex_lock(&(fork->mutex));
	if (fork->state == AVAILABLE)
	{
		fork->state = UNAVAILABLE;
		printf("%lu %i has taken a fork\n", get_actual_time_ms(), n_ph);
		state = 1;
	}
	pthread_mutex_unlock(&(fork->mutex));
	return (state);
}
