/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_tasks2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:23:52 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/26 11:11:35 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (!(ph.fork_left) && *(ph.fork_right) == AVAILABLE)
	{
		*(ph.fork_right) = UNAVAILABLE;
		printf("%lu %i has taken a fork\n", get_actual_time_ms(), ph.ph_number);
	}
	else if (*(ph.fork_right) == AVAILABLE && *(ph.fork_left) == AVAILABLE)
	{
		*(ph.fork_left) = UNAVAILABLE;
		*(ph.fork_right) = UNAVAILABLE;
		time_ms = get_actual_time_ms();
		printf("%lu %i has taken a fork\n", time_ms, ph.ph_number);
		printf("%lu %i has taken a fork\n", time_ms, ph.ph_number);
		state = EATING;
	}
	pthread_mutex_unlock(ph.mutex);
	return (state);
}

void	drop_forks(t_philo ph)
{
	pthread_mutex_lock(ph.mutex);
	*(ph.fork_left) = AVAILABLE;
	*(ph.fork_right) = AVAILABLE;
	pthread_mutex_unlock(ph.mutex);
}
