/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:25:31 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/21 12:15:15 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define HOLDING_FORKS	0
#define EATING			1
#define DROP_FORKS		2
#define SLEEPING		3
#define THINKING		4
#define DIED			5
#define EXIT			6

int holding_forks(t_philo ph);
int drop_forks(t_philo ph);
int is_eating(t_philo *ph);
int get_next_state(t_philo ph, int actual_state);
int is_sleeping(t_philo ph);
int is_thinkig(t_philo ph);

/*
void *ph_routine(void *philo)
{
	t_philo ph;
	int     have_forks;
	int     is_dead;
	int     n_cicles;

	ph = *(t_philo *) philo;
	have_forks = 0;
	is_dead = 0;
	n_cicles = 0;
	while (!is_dead)
	{
		have_forks = holding_forks(ph);
		if (have_forks)
		{
			printf("time %i is eating\n", ph.ph_number);
			drop_forks(ph);
			printf("time %i is sleeping\n", ph.ph_number);
			printf("time %i is thinking\n", ph.ph_number);
			n_cicles++;
			if (n_cicles == ph.args.nb_times_to_eat)
				is_dead = 1;
		}
	}
}
*/

void *ph_routine(void *philo)
{
	t_philo ph;
	int     state;

	ph = *(t_philo *) philo;
	state = HOLDING_FORKS;

	while (state != EXIT)
	{
		if (state == HOLDING_FORKS)
			state = holding_forks(ph);
		else if (state == EATING)
		{
			state = is_eating(&ph);
		}
		else if (state == DROP_FORKS)
		{
			state = drop_forks(ph);
		}
		else if (state == SLEEPING)
		{
			state = is_sleeping(ph);
		}
		else if (state == THINKING)
		{
			state = is_thinkig(ph);
		}
	}
}

int holding_forks(t_philo ph)
{
	unsigned long   time_ms;
	int             state;

	state = HOLDING_FORKS;
	pthread_mutex_lock(ph.mutex);
	if (*(ph.fork_left) == AVAILABLE && *(ph.fork_right) == AVAILABLE)
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

	printf("time %i is eating\n", ph->ph_number);
	state = EATING;
	state = get_next_state(*ph, state);
	(ph->n_times_of_ate)++;
	return (state);
}

int is_sleeping(t_philo ph)
{
	int state;

	printf("time %i is sleeping\n", ph.ph_number);
	state = SLEEPING;
	state = get_next_state(ph, state);
	return (state);
}

int is_thinkig(t_philo ph)
{
	int state;

	printf("time %i is thinkig\n", ph.ph_number);
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
	{
		if (ph.n_times_of_ate == ph.args.nb_times_to_eat)
			return (EXIT);
		return (HOLDING_FORKS);
	}
}

/*
int is_eating(t_philo ph)
{
	static unsigned long start_time = 0;
	int                  status;

	status = 0;
	if (!start_time)
	{
		start_time = get_actual_time_ms();
		printf("%lu %i is eating\n",start_time, ph.ph_number);
	}
	if (time_has_passed(start_time, ph.args.time_to_eat))
	{
		start_time = 0;
		status = 1;
	}
	return (status);
}
*/