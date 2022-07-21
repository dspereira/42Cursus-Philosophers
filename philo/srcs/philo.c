/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 09:48:04 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/21 11:13:26 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// number_of_philosophers

// time_to_die              -> tempo maximo que o filosofo pode passar sem comer ou morre
// time_to_eat              -> tempo que demora para comer, precisa de 2 garfos
// time_to_sleep            -> tempo que o filosofo demora a dormir

// number_of_times_each_philosopher_must_eat -> quantidade de vezes que cada filosofo tem de comer. opecional

/*
int *init_forks(t_args args)
{
	int	*forks;
	int	i;

	if (args.number_of_ph > 0)
	{
		forks = malloc(args.number_of_ph * sizeof(int));
		i = 0;
		while (i < args.number_of_ph)
		{
			forks[i] = 0;
			i++;
		}
		return (forks);
	}
	return (NULL);
}

t_philo *init_philo(t_args args, int *forks)
{
	t_philo *ph;
	int		i;

	if (args.number_of_ph > 0)
	{
		ph = malloc(args.number_of_ph * sizeof(t_philo));
		i = 0;
		while (i < args.number_of_ph)
		{
			ph[i].ph_number = i + 1;
			i++;
		}
		return (ph);
	}
	return (NULL);
}
*/

int *init_forks(int n)
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


t_philo *init_philo(int *forks, t_args args, int n, pthread_mutex_t	*mutex)
{
	t_philo *ph;
	int		i;

	
	if (n > 0)
	{
		ph = malloc(n * sizeof(t_philo));
		i = 0;
		while (i < n)
		{
			ph[i].mutex = mutex;
			ph[i].ph_number = i + 1;
			ph[i].args = args;
			ph[i].eating_time = 0;
			ph[i].sleeping_time = 0;
			ph[i].thinking_time = 0;
			ph[i].n_times_of_ate = 0;
			ph[i].fork_right = &forks[i];
			if (i == 0)
				ph[i].fork_left = &forks[n - 1];
			else 
				ph[i].fork_left = &forks[i - 1];
						
			i++;
		}
		return (ph);
	}
	return (NULL);
}

int main (int argc, char **argv)
{
	t_args	args;
	t_philo *ph;
	int		*forks;
	int		n_ph;
	pthread_mutex_t	mutex;
	
	pthread_mutex_init(&mutex, NULL);
	if (argc < 5)
	{
		printf("error\n");
		return (1);
	}
	else
	{
		n_ph = ft_atoi(argv[1]);

		args.number_of_ph = ft_atoi(argv[1]);
		args.time_to_die = ft_atoi(argv[2]);
		args.time_to_eat = ft_atoi(argv[3]);
		args.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			args.nb_times_to_eat = ft_atoi(argv[5]);
		else 
			args.nb_times_to_eat = 0;
	}
	forks = init_forks(n_ph);
	ph = init_philo(forks, args, n_ph, &mutex);

	create_threads(ph, n_ph);
	wait_threads(ph, n_ph);
	
	pthread_mutex_destroy(&mutex);

	return (0);
}
