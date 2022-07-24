/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 09:48:00 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/24 17:44:01 by dsilveri         ###   ########.fr       */
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

# define ODD			0
# define EVEN			1

#define HOLDING_FORKS	0
#define EATING			1
#define SLEEPING		2
#define THINKING		3
#define DIED			4
#define	EATED_ENOUGH	5
#define EXIT			6


typedef struct s_args
{
	unsigned long	number_of_ph;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	nb_times_to_eat;
}   t_args;

typedef struct s_time
{
	int status;
	unsigned long time;
}	t_time;

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
	unsigned long	n_times_of_ate;

	int				number_of_tasks;
	int 			*taks_end;

	int				*died;
	int				*stop_to_eat;
	int				*cycles;
	int				*cycles_1;

	int				total_cicles;

	int				odd_or_even; 

	t_time			eating;
	t_time			sleeping;

	t_args			args;
}   t_philo;

/*
typedef struct s_settings
{
	int				number_of_ph;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	nb_times_to_eat;
} t_settings;

typedef struct s_philo_1
{
	t_settings stg;
	

}   t_philo_1;
*/

/* ph_routine.c */
void *ph_routine(void *philo);

/* threads.c */
void create_threads(t_philo *ph, int n);
void wait_threads(t_philo *ph, int n);

/* utils.c */
int	ft_atoi(const char *str);
unsigned long get_actual_time_ms(void);
unsigned long time_has_passed(unsigned long start, unsigned long time);


/* ph_tasks.c */
int		is_eating(t_philo *ph);
int		is_sleeping(t_philo *ph);
int		is_thinkig(t_philo ph);
int		is_dying(t_philo ph);

/* ph_tasks2.c */
int		holding_forks(t_philo ph);
void	drop_forks(t_philo ph);

#endif