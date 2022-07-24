/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 09:48:04 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/24 15:40:17 by dsilveri         ###   ########.fr       */
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


t_philo *init_philo(int *forks, t_args args, int n, pthread_mutex_t	*mutex, int *tasks_end)
{
	t_philo *ph;
	int		i;

	int *died;
	int *stop_to_eat;
	int	*cycles;
	int	*cycles_1;
	
	died = malloc(sizeof(int));
	*died = 0;
	stop_to_eat = malloc(sizeof(int));
	*stop_to_eat = 0;
	cycles = malloc(sizeof(int));
	*cycles = EVEN;
	cycles_1 = malloc(sizeof(int));
	*cycles_1 = 0;

	if (n > 0)
	{
		ph = malloc(n * sizeof(t_philo));
		i = 0;
		while (i < n)
		{
			ph[i].number_of_tasks = args.number_of_ph;
			ph[i].taks_end = tasks_end;

			ph[i].mutex = mutex;
			ph[i].ph_number = i + 1;
			ph[i].args = args;
			ph[i].eating_time = 0;
			ph[i].sleeping_time = 0;
			ph[i].thinking_time = 0;
			ph[i].n_times_of_ate = 0;
			ph[i].eating.status = 0;
			ph[i].eating.time = 0;
			ph[i].sleeping.status = 0;
			ph[i].sleeping.time = 0;
			ph[i].died = died;
			ph[i].stop_to_eat = stop_to_eat;
			ph[i].cycles = cycles;
			ph[i].cycles_1 = cycles_1;

			ph[i].odd_or_even = ph[i].ph_number % 2;


			if (ph[i].args.number_of_ph % 2 == 0)
				ph[i].total_cicles = ph[i].args.number_of_ph / 2;
			else if(ph[i].args.number_of_ph > 1)
			{
				if (ph[i].ph_number % 2 == 0)
				{
					ph[i].total_cicles = (ph[i].args.number_of_ph / 2);
				}
				else
				{
					ph[i].total_cicles = (ph[i].args.number_of_ph / 2) + 1;
				} 
			}
			else 
				ph[i].total_cicles = 1;


			ph[i].fork_right = &forks[i];
			if (ph->args.number_of_ph > 1)
			{
				if (i == 0)
					ph[i].fork_left = &forks[n - 1];
				else 
					ph[i].fork_left = &forks[i - 1];
			}
			else
			{
				ph[i].fork_left = NULL;
			}
	
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

	int taks_end = 0;
	
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
			args.nb_times_to_eat = 2147483647;
	}
	forks = init_forks(n_ph);
	ph = init_philo(forks, args, n_ph, &mutex, &taks_end);

	create_threads(ph, n_ph);
	wait_threads(ph, n_ph);
	
	pthread_mutex_destroy(&mutex);

	return (0);
}
