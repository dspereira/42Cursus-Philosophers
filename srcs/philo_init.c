/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:47:43 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/03 12:12:24 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void			add_data_to_ph(t_philo *p, t_forks *f, t_settings s);
static void			init_data(t_philo *ph);
static t_settings	settings_init(int argc, char **argv);

t_philo	*philo_init(int argc, char **argv)
{
	t_philo		*ph;
	t_forks		*forks;
	t_settings	stg;

	stg = settings_init(argc, argv);
	forks = init_forks(stg.number_of_ph);
	ph = oom_guard(malloc(stg.number_of_ph * sizeof(t_philo)));
	save_alloc_mem(ph);
	add_data_to_ph(ph, forks, stg);
	return (ph);
}

static void	add_data_to_ph(t_philo *p, t_forks *f, t_settings s)
{
	pthread_mutex_t	*mutex;
	int				*start;
	int				*end;
	int				i;

	mutex = oom_guard(malloc(sizeof(pthread_mutex_t)));
	save_alloc_mem(mutex);
	start = oom_guard(malloc(sizeof(int)));
	save_alloc_mem(start);
	*start = 0;
	end = oom_guard(malloc(sizeof(int)));
	save_alloc_mem(end);
	*end = 0;
	i = -1;
	while (++i < s.number_of_ph)
	{
		p[i].stg = s;
		p[i].mutex = mutex;
		p[i].ph_number = i + 1;
		p[i].start = start;
		p[i].end = end;
		init_data(&p[i]);
		add_forks_to_ph(&p[i], f);
	}
	init_mutex(f, s.number_of_ph, mutex);
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

	stg.number_of_ph = input_args_error(str_to_nb(argv[1]), ARG_1);
	stg.time_to_die = input_args_error(str_to_nb(argv[2]), ARG_2);
	stg.time_to_eat = input_args_error(str_to_nb(argv[3]), ARG_3);
	stg.time_to_sleep = input_args_error(str_to_nb(argv[4]), ARG_4);
	if (argc == 6)
		stg.nb_times_to_eat = input_args_error(str_to_nb(argv[5]), ARG_5);
	else
		stg.nb_times_to_eat = 0;
	return (stg);
}
