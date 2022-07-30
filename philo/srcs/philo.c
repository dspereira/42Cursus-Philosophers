/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 09:48:04 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/30 18:24:38 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Run teste
// ./start.sh ../ 1


// number_of_philosophers

// time_to_die              -> tempo maximo que o filosofo pode passar sem comer ou morre
// time_to_eat              -> tempo que demora para comer, precisa de 2 garfos
// time_to_sleep            -> tempo que o filosofo demora a dormir

// number_of_times_each_philosopher_must_eat -> quantidade de vezes que cada filosofo tem de comer. opecional



int main (int argc, char **argv)
{
	t_philo *ph;
	int		n_ph;
	pthread_mutex_t	mutex;

	int taks_end = 0;
	
	pthread_mutex_init(&mutex, NULL);
	if (argc < 5)
	{
		printf("error\n");
		return (1);
	}

	n_ph = ft_atoi(argv[1]);
	ph = philo_init(argc, argv, &mutex);

	create_threads(ph, n_ph);
	wait_threads(ph, n_ph);
	
	pthread_mutex_destroy(&mutex);

	return (0);
}
