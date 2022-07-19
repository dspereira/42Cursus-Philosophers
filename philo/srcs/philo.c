/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 09:48:04 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/19 16:16:30 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// number_of_philosophers

// time_to_die              -> tempo maximo que o filosofo pode passar sem comer ou morre
// time_to_eat              -> tempo que demora para comer, precisa de 2 garfos
// time_to_sleep            -> tempo que o filosofo demora a dormir

// number_of_times_each_philosopher_must_eat -> quantidade de vezes que cada filosofo tem de comer. opecional

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
			return (ph);
		}
	}
	return (NULL);
}

int main (int argc, char **argv)
{
	t_args	args;
	t_philo *ph;
	int		*forks;
	pthread_t t1, t2;
	
	if (argc < 5)
	{
		printf("error\n");
		return (1);
	}
	else
	{
		args.number_of_ph = ft_atoi(argv[1]);
		args.time_to_die = ft_atoi(argv[2]);
		args.time_to_eat = ft_atoi(argv[3]);
		args.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			args.nb_times_to_eat = ft_atoi(argv[5]);
		else 
			args.nb_times_to_eat = 0;
	}
	forks = init_forks(args);
	ph = init_philo(args, forks);

    pthread_create(&(ph[0].thread), NULL, &ph_routine, &ph[0]);
	pthread_create(&(ph[1].thread), NULL, &ph_routine, &ph[1]);
	pthread_join(ph[0].thread, NULL);
	pthread_join(ph[1].thread, NULL);
	
	return (0);
}
