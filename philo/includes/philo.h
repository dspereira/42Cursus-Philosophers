/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 09:48:00 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/20 15:43:53 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define UNAVAILABLE	1
# define AVAILABLE		0


typedef struct s_args
{
	unsigned long	number_of_ph;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	nb_times_to_eat;
}   t_args;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*mutex;
	int 			*fork_left;
	int				*fork_right;
	unsigned long	ph_number;
	unsigned long	eating_time;
	unsigned long	sleeping_time;
	unsigned long	thinking_time;
	t_args			args;
}   t_philo;


/* ph_routine.c */
void *ph_routine(void *philo);

/* threads.c */
void create_threads(t_philo *ph, int n);
void wait_threads(t_philo *ph, int n);

/* utils.c */
int	ft_atoi(const char *str);


#endif