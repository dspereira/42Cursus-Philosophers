/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:47:43 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/30 19:19:13 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void			init_data(t_philo *ph);
static t_settings	settings_init(int argc, char **argv);
static t_forks		*init_forks(int n);
static void			add_forks_to_ph(t_philo *ph, t_forks *forks);

t_philo	*philo_init(int argc, char **argv, pthread_mutex_t *mutex)
{
	t_philo		*ph;
	t_forks		*forks;
	t_settings	stg;
	int			*died;
	int			i;

	stg = settings_init(argc, argv);
	forks = init_forks(stg.number_of_ph);
	ph = malloc(stg.number_of_ph * sizeof(t_philo));
	died = malloc(sizeof(int));
	*died = 0;
	i = 0;
	while (i < stg.number_of_ph)
	{
		ph[i].stg = stg;
		ph[i].mutex = mutex;
		ph[i].ph_number = i + 1;
		ph[i].died = died;
		init_data(&ph[i]);
		add_forks_to_ph(&ph[i], forks);
		i++;
	}
	return (ph);
}

static void	init_data(t_philo *ph)
{
	ph->n_forks_hold = 0;
	ph->eating.status = 0;
	ph->eating.time = 0;
	ph->sleeping.status = 0;
	ph->sleeping.time = 0;
	ph->n_times_of_ate = 0;
}

static t_settings	settings_init(int argc, char **argv)
{
	t_settings	stg;

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

static t_forks	*init_forks(int n)
{
	t_forks	*forks;
	int		i;

	if (n > 0)
	{
		forks = malloc(n * sizeof(t_forks));
		i = 0;
		while (i < n)
		{
			forks[i].state = AVAILABLE;
			pthread_mutex_init(&(forks[i].mutex), NULL);
			i++;
		}
		return (forks);
	}
	return (NULL);
}

static void	add_forks_to_ph(t_philo *ph, t_forks *forks)
{
	int	fork_index;

	ph->forks = forks;
	fork_index = ph->ph_number - 1;
	ph->fork_right = &forks[fork_index];
	if (ph->stg.number_of_ph > 1)
	{
		if (ph->ph_number == ph->stg.number_of_ph)
			ph->fork_left = &forks[0];
		else
			ph->fork_left = &forks[fork_index + 1];
	}
	else
		ph->fork_left = NULL;
}
