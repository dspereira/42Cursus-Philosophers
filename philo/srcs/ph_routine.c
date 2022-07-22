/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:25:31 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/22 18:21:44 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define HOLDING_FORKS	0
#define EATING			1
#define DROP_FORKS		2
#define SLEEPING		3
#define THINKING		4
#define DIED			5
#define	EATED_ENOUGH	6
#define EXIT			7

int holding_forks(t_philo ph);
int drop_forks(t_philo ph);
int is_eating(t_philo *ph);
int get_next_state(t_philo ph, int actual_state);
int is_sleeping(t_philo *ph);
int is_thinkig(t_philo ph);
void check_ph_death(t_philo ph);

int is_ph_death(t_philo *ph);

int is_dead(t_philo *ph, int actual_state);

int ph_died(t_philo ph);

int check_ph_is_dead(t_philo *ph, int actual_state);

int check_of_times_eat(t_philo *ph, int actual_state);

void *ph_routine(void *philo)
{
	t_philo ph;
	int     state;

	ph = *(t_philo *) philo;
	state = HOLDING_FORKS;

	while (state != EXIT)
	{
		state = check_ph_is_dead(&ph, state);
		state = check_of_times_eat(&ph, state);
		if (state == HOLDING_FORKS)
			state = holding_forks(ph);
		else if (state == EATING)
			state = is_eating(&ph);
		else if (state == DROP_FORKS)
			state = drop_forks(ph);
		else if (state == SLEEPING)
			state = is_sleeping(&ph);
		else if (state == THINKING)
			state = is_thinkig(ph);
		else if (state == DIED)
			state = ph_died(ph);
		else if (state == EATED_ENOUGH)
			state = EXIT;
	}
}

int holding_forks(t_philo ph)
{
	unsigned long   time_ms;
	int             state;

	state = HOLDING_FORKS;
	pthread_mutex_lock(ph.mutex);
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
		state = get_next_state(ph, state);
	}
	pthread_mutex_unlock(ph.mutex);
	return (state);
}

int drop_forks(t_philo ph)
{
	pthread_mutex_lock(ph.mutex);
	*(ph.fork_left) = AVAILABLE;
	*(ph.fork_right) = AVAILABLE;
	pthread_mutex_unlock(ph.mutex);
	return(get_next_state(ph, DROP_FORKS));
}

int is_eating(t_philo *ph)
{
	int state;

	state = EATING;
	if (!ph->eating.status)
	{
		ph->eating.status = 1;
		ph->eating.time = get_actual_time_ms();
		printf("%lu %i is eating\n",ph->eating.time, ph->ph_number);
	}
	else if (time_has_passed(ph->eating.time, ph->args.time_to_eat))
	{
		ph->eating.status = 0;
		(ph->n_times_of_ate)++;
		state = get_next_state(*ph, state);
	}
	return (state);
}

int is_sleeping(t_philo *ph)
{
	int state;

	state = SLEEPING;
	if (!ph->sleeping.status)
	{
		ph->sleeping.status = 1;
		ph->sleeping.time = get_actual_time_ms();
		printf("%lu %i is sleeping\n",ph->sleeping.time, ph->ph_number);
	}
	else if (time_has_passed(ph->sleeping.time, ph->args.time_to_sleep))
	{
		ph->sleeping.status = 0;
		state = get_next_state(*ph, state);
	}
	return (state);
}

int is_thinkig(t_philo ph)
{
	int state;

	printf("%lu %i is thinkig\n",get_actual_time_ms(), ph.ph_number);
	state = THINKING;
	state = get_next_state(ph, state);
	return (state);
}


int get_next_state(t_philo ph, int actual_state)
{
	if (actual_state == HOLDING_FORKS)
		return (EATING);
	else if (actual_state == EATING)
		return (DROP_FORKS);
	else if (actual_state == DROP_FORKS)
		return (SLEEPING);
	else if (actual_state == SLEEPING)
		return (THINKING);
	else if (actual_state == THINKING)
		return (HOLDING_FORKS);
}

int check_ph_is_dead(t_philo *ph, int actual_state)
{
	int state;

	state = actual_state;
	pthread_mutex_lock(ph->mutex);
	if (*(ph->died))
		state = DIED;
	else if(time_has_passed(ph->eating.time, ph->args.time_to_die))
	{
		*(ph->died) = ph->ph_number;
		state = DIED;
	}
	pthread_mutex_unlock(ph->mutex);
	return (state);
}

int ph_died(t_philo ph)
{
	if (*ph.died == ph.ph_number)
		printf("%lu %i died\n", get_actual_time_ms(), ph.ph_number);
	return (EXIT);
}

int check_of_times_eat(t_philo *ph, int actual_state)
{
	int state;

	state = actual_state;
	pthread_mutex_lock(ph->mutex);
	if (*(ph->stop_to_eat))
		state = EATED_ENOUGH;
	if (ph->n_times_of_ate == ph->args.nb_times_to_eat)
	{
		*(ph->stop_to_eat) = 1;
		state = EATED_ENOUGH;
	}
	pthread_mutex_unlock(ph->mutex);
	return (state);
}
