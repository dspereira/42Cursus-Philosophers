/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:25:31 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/30 17:23:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_ph_is_dead(t_philo *ph, int actual_state);
static int	check_of_times_eat(t_philo *ph, int actual_state);

void	*ph_routine(void *philo)
{
	t_philo	ph;
	int		state;

	ph = *(t_philo *) philo;
	time_counter_ini(ph.mutex);
	state = HOLDING_FORKS;
	if (ph.ph_number % 2 == 0)
		usleep(2000);
	if (ph.stg.number_of_ph % 2 != 0 && ph.ph_number == ph.stg.number_of_ph)
		usleep(500);
	while (state != EXIT)
	{
		usleep(100);
		state = check_ph_is_dead(&ph, state);
		if (!ph.stg.nb_times_to_eat_ultd)
			state = check_of_times_eat(&ph, state);
		if (state == HOLDING_FORKS)
			state = holding_forks(&ph);
		else if (state == EATING)
			state = is_eating(&ph);
		else if (state == SLEEPING)
			state = is_sleeping(&ph);
		else if (state == THINKING)
			state = is_thinkig(ph);
		else if (state == DIED)
			state = is_dying(ph);
		else if (state == EATED_ENOUGH)
			state = EXIT;
	}
}

static int	check_ph_is_dead(t_philo *ph, int actual_state)
{
	int	state;

	state = actual_state;
	pthread_mutex_lock(ph->mutex);
	if (*(ph->died))
		state = DIED;
	else if (time_has_passed(ph->eating.time, ph->stg.time_to_die))
	{
		*(ph->died) = ph->ph_number;
		state = DIED;
	}
	pthread_mutex_unlock(ph->mutex);
	return (state);
}

static int	check_of_times_eat(t_philo *ph, int actual_state)
{
	int	state;

	state = actual_state;
	if (ph->n_times_of_ate == ph->stg.nb_times_to_eat)
		state = EATED_ENOUGH;
	return (state);
}
