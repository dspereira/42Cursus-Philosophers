/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 09:48:00 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/30 17:28:23 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define UNAVAILABLE	0
# define AVAILABLE		1

# define ODD			1
# define EVEN			0

#define HOLDING_FORKS	0
#define EATING			1
#define SLEEPING		2
#define THINKING		3
#define DIED			4
#define	EATED_ENOUGH	5
#define EXIT			6

typedef struct s_time
{
	int				status;
	unsigned long	time;
}	t_time;

typedef struct s_forks
{
	int				state;
	pthread_mutex_t	mutex;
}	t_forks;

typedef struct s_settings
{
	int				number_of_ph;
	int				nb_times_to_eat_ultd;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	nb_times_to_eat;
} t_settings;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*mutex;
	t_settings		stg;
	t_time			eating;
	t_time			sleeping;
	t_forks			*forks;
	t_forks			*fork_right;
	t_forks			*fork_left;
	int				ph_number;
	int				*died;
	int				n_times_of_ate;
	int				n_forks_hold;
}   t_philo;



/* ph_routine.c */
void *ph_routine(void *philo);

/* threads.c */
void create_threads(t_philo *ph, int n);
void wait_threads(t_philo *ph, int n);

/* utils.c */
int	ft_atoi(const char *str);

/* ph_tasks.c */
int		is_eating(t_philo *ph);
int		is_sleeping(t_philo *ph);
int		is_thinkig(t_philo ph);
int		is_dying(t_philo ph);

/* ph_tasks2.c */
//int		holding_forks(t_philo ph);
int	holding_forks(t_philo *ph);
void	drop_forks(t_philo ph);

/* time_counter.c */
void time_counter_ini(pthread_mutex_t *mutex);
unsigned long get_actual_time_ms(void);
unsigned long time_has_passed(unsigned long start, unsigned long time);

/* philo_init.c */
t_philo *philo_init(int argc, char **argv, pthread_mutex_t *mutex);

#endif