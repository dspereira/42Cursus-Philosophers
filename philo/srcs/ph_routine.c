/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:25:31 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/21 18:33:55 by dsilveri         ###   ########.fr       */
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
int is_eating(t_philo *ph, unsigned long *time);
int get_next_state(t_philo ph, int actual_state);
int is_sleeping(t_philo *ph);
int is_thinkig(t_philo ph);

void *ph_routine(void *philo)
{
	t_philo ph;
	int     state;
	unsigned long start_time;

	ph = *(t_philo *) philo;
	state = HOLDING_FORKS;

	start_time = get_actual_time_ms();

	while (state != EXIT)
	{
		pthread_mutex_lock(ph.mutex);
		if (*ph.taks_end == ph.number_of_tasks)
		{
			pthread_mutex_unlock(ph.mutex);
			return (NULL);
		}
		if (time_has_passed(start_time, ph.args.time_to_die))
		{
			*ph.taks_end = ph.number_of_tasks;
			printf("%lu %i died\n", get_actual_time_ms(), ph.ph_number);
			pthread_mutex_unlock(ph.mutex);
			return (NULL);
		}
		pthread_mutex_unlock(ph.mutex);
		if (state == HOLDING_FORKS)
			state = holding_forks(ph);
		else if (state == EATING)
		{
			state = is_eating(&ph, &start_time);
		}
		else if (state == DROP_FORKS)
		{
			state = drop_forks(ph);
		}
		else if (state == SLEEPING)
		{
			state = is_sleeping(&ph);
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
	if (!(ph.fork_left) && *(ph.fork_right) == AVAILABLE)
	{
		*(ph.fork_right) = UNAVAILABLE;
		time_ms = get_actual_time_ms();
		printf("%lu %i has taken a fork\n", time_ms, ph.ph_number);
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
	if (ph.fork_left)
		*(ph.fork_left) = AVAILABLE;
	*(ph.fork_right) = AVAILABLE;
	pthread_mutex_unlock(ph.mutex);
	return(get_next_state(ph, DROP_FORKS));
}

int is_eating(t_philo *ph, unsigned long *time)
{
	int state;

	state = EATING;
	if (!ph->eating.status)
	{
		ph->eating.status = 1;
		ph->eating.time = get_actual_time_ms();
		*time = get_actual_time_ms();
		printf("%lu %i is eating\n",ph->eating.time, ph->ph_number);
	}
	else if (time_has_passed(ph->eating.time, ph->args.time_to_eat))
	{
		ph->eating.status = 0;
		(ph->n_times_of_ate)++;
		pthread_mutex_lock(ph->mutex);
		if (ph->n_times_of_ate == ph->args.nb_times_to_eat)
			(*ph->taks_end)++;
		pthread_mutex_unlock(ph->mutex);
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
	{
		if (ph.n_times_of_ate == ph.args.nb_times_to_eat)
			return (EXIT);
		return (HOLDING_FORKS);
	}
}
