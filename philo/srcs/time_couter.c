/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_couter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:47:30 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/25 10:36:27 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned long	get_offset_time(void);

void	time_counter_ini(pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	get_offset_time();
	pthread_mutex_unlock(mutex);
}

unsigned long	get_actual_time_ms(void)
{
	struct timeval	t;
	unsigned long	time_ms;
	unsigned long	offset;

	gettimeofday(&t, NULL);
	offset = get_offset_time();
	time_ms = ((t.tv_sec * 1000) + (t.tv_usec / 1000)) - offset;
	return (time_ms);
}

unsigned long	time_has_passed(unsigned long start, unsigned long time)
{
	unsigned long	actual;

	actual = get_actual_time_ms();
	if ((actual - start) >= time)
		return (actual);
	return (0);
}

static unsigned long	get_offset_time(void)
{
	static unsigned long	offset = 0;
	struct timeval			t;

	if (!offset)
	{
		gettimeofday(&t, NULL);
		offset = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	}
	return (offset);
}
