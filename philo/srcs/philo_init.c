/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:47:43 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/26 16:59:12 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_settings settings_init(int argc, char **argv);
static t_forks *init_forks(int n);
static void add_forks_to_ph(t_philo *ph, t_forks *forks);
static void add_data_to_ph(t_philo *ph, t_settings stg, t_forks *forks, pthread_mutex_t *mutex);
static void add_data_to_ph2(t_philo *ph);

t_philo *philo_init(int argc, char **argv, pthread_mutex_t *mutex)
{
	t_philo		*ph;
	t_settings	stg;
	t_forks		*forks;

	stg = settings_init(argc, argv);
	ph = malloc(stg.number_of_ph * sizeof(t_philo));
	forks = init_forks(stg.number_of_ph);
	add_data_to_ph(ph, stg, forks, mutex);
	return (ph);
}

static void add_data_to_ph(t_philo *ph, t_settings stg, t_forks *forks, pthread_mutex_t *mutex)
{
	int	*died;
	int	*cycles;
	int	*can_hold_fork;
	int	i;

	died = malloc(sizeof(int));
	*died = 0;
	cycles = malloc(sizeof(int));
	*cycles = 0;
	can_hold_fork = malloc(sizeof(int));
	*can_hold_fork = ODD;
	i = 0;
	while (i < stg.number_of_ph)
	{
		ph[i].stg = stg;
		ph[i].mutex = mutex;
		ph[i].ph_number = i + 1;
		ph[i].can_hold_fork = can_hold_fork;
		ph[i].cycles = cycles;
		ph[i].died = died;
		add_data_to_ph2(&ph[i]);
		add_forks_to_ph(&ph[i], forks);
		i++;
	}
}

static void add_data_to_ph2(t_philo *ph)
{
	ph->eating.status = 0;
	ph->eating.time = 0;
	ph->sleeping.status = 0;
	ph->sleeping.time = 0;
	ph->n_times_of_ate = 0;
	ph->odd_even = ph->ph_number % 2;
	if (ph->stg.number_of_ph % 2 == 0)
		ph->total_cycles = ph->stg.number_of_ph / 2;
	else
	{
		if (ph->ph_number % 2 == 0)
			ph->total_cycles = (ph->stg.number_of_ph / 2);
		else
			ph->total_cycles = (ph->stg.number_of_ph / 2) + 1;
	}	
}

static t_settings settings_init(int argc, char **argv)
{
	t_settings stg;
	
	stg.number_of_ph = ft_atoi(argv[1]);
	stg.time_to_die = ft_atoi(argv[2]);
	stg.time_to_eat = ft_atoi(argv[3]);
	stg.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		stg.nb_times_to_eat = ft_atoi(argv[5]);
		stg.nb_times_to_eat_ultd = 0;
	}
	else
	{
		stg.nb_times_to_eat = 0;
		stg.nb_times_to_eat_ultd = 1;
	}
	return (stg);
}

static t_forks *init_forks(int n)
{
	t_forks	*forks;
	int	i;
	
	if (n > 0)
	{
		forks = malloc(n * sizeof(t_forks));
		i = 0;
		while (i < n)
		{
			forks[i].fork = AVAILABLE;
			pthread_mutex_init(&(forks[i].mutex), NULL);
			i++;
		}
		return (forks);
	}
	return (NULL);
}

static void add_forks_to_ph(t_philo *ph, t_forks *forks)
{
	int fork_index;

	ph->forks = forks;
	fork_index = ph->ph_number - 1;
	ph->fork_right = &forks[fork_index];
	if (ph->stg.number_of_ph > 1)
	{
		if (fork_index == 0)
			ph->fork_left = &forks[ph->stg.number_of_ph - 1];
		else 
			ph->fork_left = &forks[fork_index - 1];
	}
	else
	{
		ph->fork_left = NULL;
	}
}