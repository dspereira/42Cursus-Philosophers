/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:25:31 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/03 17:40:24 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	wait_for_all_threads_ready(t_philo ph);
static int	is_ph_dead(t_philo *ph);
static int	check_end_of_simul(t_philo *ph, int actual_state);

void	*ph_routine(void *philo)
{
	t_philo	ph;
	int		state;

	ph = *(t_philo *) philo;
	state = wait_for_all_threads_ready(ph);
	time_counter_ini(ph.mutex);
	if (ph.ph_number % 2 == 0)
		usleep(2000);
	if (ph.stg.number_of_ph % 2 != 0 && ph.ph_number == ph.stg.number_of_ph)
		usleep(500);
	while (state != EXIT)
	{
		usleep(100);
		state = check_end_of_simul(&ph, state);
		if (state == HOLDING_FORKS)
			state = holding_forks(&ph);
		else if (state == EATING)
			state = is_eating(&ph);
		else if (state == SLEEPING)
			state = is_sleeping(&ph);
		else if (state == THINKING)
			state = is_thinkig(ph);
	}
	return (NULL);
}

static int	wait_for_all_threads_ready(t_philo ph)
{
	int	state;
	int	i;

	pthread_mutex_lock(ph.mutex);
	*(ph.start) += 1;
	pthread_mutex_unlock(ph.mutex);
	i = -1;
	while (1)
	{
		pthread_mutex_lock(ph.mutex);
		if (*(ph.start) == ph.stg.number_of_ph)
		{
			state = HOLDING_FORKS;
			pthread_mutex_unlock(ph.mutex);
			break ;
		}
		pthread_mutex_unlock(ph.mutex);
		if (++i >= 200)
		{
			state = EXIT;
			break ;
		}
		usleep(10);
	}
	return (state);
}

static int	is_ph_dead(t_philo *ph)
{
	int	state;

	state = 0;
	if (time_has_passed(ph->eating.time, ph->stg.time_to_die))
	{
		*(ph->end) = ph->stg.number_of_ph;
		printf("%lu %i died\n", get_actual_time_ms(), ph->ph_number);
		state = 1;
	}
	return (state);
}

static int	check_end_of_simul(t_philo *ph, int actual_state)
{
	int	state;

	state = actual_state;
	pthread_mutex_lock(ph->mutex);
	if (*(ph->end) == ph->stg.number_of_ph || is_ph_dead(ph))
		state = EXIT;
	pthread_mutex_unlock(ph->mutex);
	return (state);
}
