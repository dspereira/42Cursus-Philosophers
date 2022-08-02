/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:25:31 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/02 16:42:06 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_ph_is_dead(t_philo *ph, int actual_state);
static int	check_of_times_eat(t_philo *ph, int actual_state);

static int check_end_of_simul(t_philo *ph, int actual_state);


void	*ph_routine(void *philo)
{
	t_philo	ph;
	int		state;

	ph = *(t_philo *) philo;

	pthread_mutex_lock(ph.mutex);
	*(ph.start) += 1;
	pthread_mutex_unlock(ph.mutex);
	usleep(2000);
	pthread_mutex_lock(ph.mutex);
	if (*(ph.start) != ph.stg.number_of_ph)
	{
		//pthread_mutex_unlock(ph.mutex);
		//return (NULL);
		state = EXIT;

	}
	else
		state = HOLDING_FORKS;
	pthread_mutex_unlock(ph.mutex);

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



/*
static int	is_ph_dead(t_philo *ph)
{
	if (time_has_passed(ph->eating.time, ph->stg.time_to_die))
		return (1);
	return (0);
}

static int	is_all_ph_ate_enough(t_philo *ph)
{
	if (*(ph->end) == ph->stg.number_of_ph)
		return (1);
	return (0);
}

static int check_end_of_simul(t_philo *ph, int actual_state)
{
	int state;

	state = actual_state;
	pthread_mutex_lock(ph->mutex);
	if (is_ph_dead(ph) || is_all_ph_ate_enough(ph))
	{
		*(ph->end) = ph->stg.number_of_ph;
		state = EXIT;
	}
	pthread_mutex_unlock(ph->mutex);
	return (state);
}
*/

static int	is_ph_dead(t_philo *ph)
{
	int	state;

	state = 0;
	if (time_has_passed(ph->eating.time, ph->stg.time_to_die))
	{
		//pthread_mutex_lock(ph->mutex);
		*(ph->end) = ph->stg.number_of_ph;
		//pthread_mutex_unlock(ph->mutex);
		printf("%lu %i died\n", get_actual_time_ms(), ph->ph_number);
		state = 1;
	}
	return (state);
}

static int	is_all_ph_ate_enough(t_philo *ph)
{
	int state;

	state = 0;

	//pthread_mutex_lock(ph->mutex);
	if (*(ph->end) == ph->stg.number_of_ph)
		state = 1;
	//pthread_mutex_unlock(ph->mutex);
	return (state);
}

static int check_end_of_simul(t_philo *ph, int actual_state)
{
	int state;

	state = actual_state;
	/*pthread_mutex_lock(ph->mutex);
	if (*(ph->end) == ph->stg.number_of_ph)
		state = EXIT
	pthread_mutex_unlock(ph->mutex);*/
	pthread_mutex_lock(ph->mutex);
	if (*(ph->end) == ph->stg.number_of_ph || is_ph_dead(ph) || is_all_ph_ate_enough(ph))
		state = EXIT;
	pthread_mutex_unlock(ph->mutex);
	return (state);
}