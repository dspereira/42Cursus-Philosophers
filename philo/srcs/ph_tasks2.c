/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_tasks2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:23:52 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/26 17:18:41 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	holding_forks(t_philo ph)
{
	unsigned long	time_ms;
	int				state;

	state = HOLDING_FORKS;
	//pthread_mutex_lock(ph.mutex);
	if (!(*ph.can_hold_fork == ph.odd_even))
	{

		//pthread_mutex_unlock(ph.mutex);
		return (state);
	}
	if (!(ph.fork_left) && ph.fork_right->fork == AVAILABLE)
	{
		pthread_mutex_lock(&(ph.fork_right->mutex));
		ph.fork_right->fork = UNAVAILABLE;
		pthread_mutex_unlock(&(ph.fork_right->mutex));
		printf("%lu %i has taken a fork\n", get_actual_time_ms(), ph.ph_number);
	}
	else if (ph.fork_right->fork == AVAILABLE && ph.fork_left->fork == AVAILABLE)
	{
		pthread_mutex_lock(&(ph.fork_left->mutex));
		ph.fork_left->fork = UNAVAILABLE;
		pthread_mutex_unlock(&(ph.fork_left->mutex));
		pthread_mutex_lock(&(ph.fork_right->mutex));
		ph.fork_right->fork = UNAVAILABLE;
		pthread_mutex_unlock(&(ph.fork_right->mutex));
		time_ms = get_actual_time_ms();
		printf("%lu %i has taken a fork\n", time_ms, ph.ph_number);
		printf("%lu %i has taken a fork\n", time_ms, ph.ph_number);
		state = EATING;
	}
	//pthread_mutex_unlock(ph.mutex);

	return (state);
}

//ph.fork_left->state
//ph.fork_left->mutex 
void	drop_forks(t_philo ph)
{
	//pthread_mutex_lock(ph.mutex);
	pthread_mutex_lock(&(ph.fork_left->mutex));
	ph.fork_left->fork = AVAILABLE;
	pthread_mutex_unlock(&(ph.fork_left->mutex));
	pthread_mutex_lock(&(ph.fork_right->mutex));
	ph.fork_right->fork = AVAILABLE;
	pthread_mutex_unlock(&(ph.fork_right->mutex));
	//pthread_mutex_unlock(ph.mutex);

	
}
