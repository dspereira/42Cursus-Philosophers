/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_tasks2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:23:52 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/30 16:39:52 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int hold_fork(t_forks *fork);
void drop_fork(t_forks *fork);

/*
int	holding_forks(t_philo ph)
{
	unsigned long	time_ms;
	int				state;

	state = HOLDING_FORKS;
	pthread_mutex_lock(ph.mutex);
	if (!(*ph.can_hold_fork == ph.odd_even))
	{
		pthread_mutex_unlock(ph.mutex);
		return (state);
	}
	pthread_mutex_unlock(ph.mutex);

	if (ph.ph_number % 2 == 0)
	{
		pthread_mutex_lock(&(ph.fork_left->mutex));
		pthread_mutex_lock(&(ph.fork_right->mutex));
	}
	else
	{
		pthread_mutex_lock(&(ph.fork_right->mutex));		
		pthread_mutex_lock(&(ph.fork_left->mutex));
	}
	if (!(ph.fork_left) && ph.fork_right->fork == AVAILABLE)
	{
		ph.fork_right->fork = UNAVAILABLE;
		printf("%lu %i has taken a fork\n", get_actual_time_ms(), ph.ph_number);
	}
	else if (ph.fork_right->fork == AVAILABLE && ph.fork_left->fork == AVAILABLE)
	{
		ph.fork_left->fork = UNAVAILABLE;
		ph.fork_right->fork = UNAVAILABLE;
		time_ms = get_actual_time_ms();
		printf("%lu %i has taken a fork\n", time_ms, ph.ph_number);
		printf("%lu %i has taken a fork\n", time_ms, ph.ph_number);
		state = EATING;
	}
	if (ph.ph_number % 2 == 0)
	{
		pthread_mutex_unlock(&(ph.fork_left->mutex));
		pthread_mutex_unlock(&(ph.fork_right->mutex));
	}
	else
	{
		pthread_mutex_unlock(&(ph.fork_right->mutex));		
		pthread_mutex_unlock(&(ph.fork_left->mutex));
	}	
	return (state);
}
*/

/*
void	drop_forks(t_philo ph)
{
	pthread_mutex_lock(&(ph.fork_left->mutex));
	ph.fork_left->fork = AVAILABLE;
	pthread_mutex_unlock(&(ph.fork_left->mutex));
	pthread_mutex_lock(&(ph.fork_right->mutex));
	ph.fork_right->fork = AVAILABLE;
	pthread_mutex_unlock(&(ph.fork_right->mutex));
}
*/

int	holding_forks(t_philo *ph)
{
	int				state;

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
	ph.fork_left->fork = AVAILABLE;
	pthread_mutex_unlock(&(ph.fork_left->mutex));
	pthread_mutex_lock(&(ph.fork_right->mutex));
	ph.fork_right->fork = AVAILABLE;
	pthread_mutex_unlock(&(ph.fork_right->mutex));
}

int hold_fork(t_forks *fork)
{
	int state;
	
	state = 0;
	if (!fork)
		return (state);
	pthread_mutex_lock(&(fork->mutex));
	if (fork->fork == AVAILABLE)
	{
		fork->fork = UNAVAILABLE;
		state = 1;
	}
	pthread_mutex_unlock(&(fork->mutex));
	return (state);
}

void	drop_fork(t_forks *fork)
{
	pthread_mutex_lock(&(fork->mutex));
	fork->fork = AVAILABLE;
	pthread_mutex_unlock(&(fork->mutex));	
}
