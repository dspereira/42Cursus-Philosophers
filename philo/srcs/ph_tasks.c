/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_tasks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:04:29 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/28 16:50:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_eating(t_philo *ph)
{
	int	state;

	state = EATING;
	if (!ph->eating.status)
	{
		ph->eating.status = 1;
		ph->eating.time = get_actual_time_ms();
		printf("%lu %i is eating\n", ph->eating.time, ph->ph_number);
	}
	else if (time_has_passed(ph->eating.time, ph->stg.time_to_eat))
	{
		ph->eating.status = 0;
		(ph->n_times_of_ate)++;
		drop_forks(*ph);
		state = SLEEPING;
	}
	return (state);
}

int	is_sleeping(t_philo *ph)
{
	int	state;

	state = SLEEPING;
	if (!ph->sleeping.status)
	{
		ph->sleeping.status = 1;
		ph->sleeping.time = get_actual_time_ms();
		printf("%lu %i is sleeping\n", ph->sleeping.time, ph->ph_number);
	}
	else if (time_has_passed(ph->sleeping.time, ph->stg.time_to_sleep))
	{
		ph->sleeping.status = 0;
		state = THINKING;
	}
	return (state);
}

int	is_thinkig(t_philo ph)
{
	printf("%lu %i is thinkig\n", get_actual_time_ms(), ph.ph_number);
	return (HOLDING_FORKS);
}

int	is_dying(t_philo ph)
{
	if (*ph.died == ph.ph_number)
		printf("%lu %i died\n", get_actual_time_ms(), ph.ph_number);
	return (EXIT);
}
