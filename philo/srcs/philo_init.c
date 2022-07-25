/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:47:43 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/25 18:14:53 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_settings settings_init(int argc, char **argv);
static int *init_forks(int n);
static void add_forks_to_ph(t_philo *ph, int *forks);

t_philo *philo_init(int argc, char **argv, pthread_mutex_t *mutex)
{
	t_philo		*ph;
	t_settings	stg;
	int			i;
	int			*forks;

	int *died;
	int	*cycles;
	int	*can_hold_fork;
	
	died = malloc(sizeof(int));
	*died = 0;
	cycles = malloc(sizeof(int));
	*cycles = 0;
	can_hold_fork = malloc(sizeof(int));
	*can_hold_fork = EVEN;

	stg = settings_init(argc, argv);
	ph = malloc(stg.number_of_ph * sizeof(t_philo));
	forks = init_forks(stg.number_of_ph);
	
	i = 0;

	while (i < stg.number_of_ph)
	{
		ph[i].stg = stg;
		ph[i].mutex = mutex;
		ph[i].ph_number = i + 1;
		ph[i].eating.status = 0;
		ph[i].eating.time = 0;
		ph[i].sleeping.status = 0;
		ph[i].sleeping.time = 0;

		ph[i].died = died;
		ph[i].n_times_of_ate = 0;
		


		
		ph[i].can_hold_fork = can_hold_fork;
		ph[i].cycles = cycles;
		ph[i].odd_even = ph[i].ph_number % 2;


		if (ph[i].stg.number_of_ph % 2 == 0)
			ph[i].total_cycles = ph[i].stg.number_of_ph / 2;
		else
		{
			if (ph[i].ph_number % 2 == 0)
				ph[i].total_cycles = (ph[i].stg.number_of_ph / 2);
			else
				ph[i].total_cycles = (ph[i].stg.number_of_ph / 2) + 1;
		}	
		add_forks_to_ph(&ph[i], forks);
		
		i++;
	}
	return (ph);
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

static int *init_forks(int n)
{
	int	*forks;
	int	i;
	
	if (n > 0)
	{
		forks = malloc(n * sizeof(int));
		i = 0;
		while (i < n)
		{
			forks[i] = AVAILABLE;
			i++;
		}
		return (forks);
	}
	return (NULL);
}

static void add_forks_to_ph(t_philo *ph, int *forks)
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