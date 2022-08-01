/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 09:48:00 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/01 16:16:25 by dsilveri         ###   ########.fr       */
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

#define HOLDING_FORKS	0
#define EATING			1
#define SLEEPING		2
#define THINKING		3
#define DIED			4
#define	EATED_ENOUGH	5
#define EXIT			6

#define	ARG_1			"number_of_philosophers\n"
#define	ARG_2			"time_to_die\n"
#define	ARG_3			"time_to_eat\n"
#define	ARG_4			"time_to_sleep\n"
#define	ARG_5			"number_of_times_each_philosopher_must_eat\n"

#define PTHREAD_CREATE	"Error create pthread\n"
#define MUTEX_INIT		"Error mutex init\n"

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

typedef struct s_alloc_mem
{
	void	*data;
}	t_alloc_mem;

/* ph_routine.c */
void *ph_routine(void *philo);

/* threads.c */
void create_threads(t_philo *ph, int n);
void wait_threads(t_philo *ph, int n);

/* utils.c */
int str_to_nb(char *str);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);

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

/* error_handler.c */
void	*oom_guard(void *p);
void	*oom_guard2(void *p);
int input_args_error(int arg, char *arg_type);
void number_input_args_error(int argc);
void thread_error(int err, char *type_error);

/* alloc_mem.c */
void	init_alloc_mem(void);
void	save_alloc_mem(void *data);
void	free_alloc_mem(void);

void destroy_forks_mutex(t_forks *forks, int n);

#endif