/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 09:47:55 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/24 11:37:50 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	long int	num;
	int			mult;

	i = 0;
	num = 0;
	mult = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			mult = -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		num = (num * 10) + str[i] - 48;
		i++;
	}
	return ((int)(num * mult));
}

/*
unsigned long get_actual_time_ms(void)
{
	struct timeval t;
    unsigned long time_ms;
	static unsigned long offset = 0; 
    
	gettimeofday(&t, NULL);
	time_ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	if (!offset)
		offset = time_ms;
    time_ms -= offset;
	return (time_ms);
}
*/

unsigned long get_actual_time_ms(void)
{
	struct timeval t;
    unsigned long time_ms;
	static unsigned long offset = 0; 
    
	gettimeofday(&t, NULL);
	time_ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	if (!offset)
	{
		offset = time_ms;
		while (1)
		{
			gettimeofday(&t, NULL);
			time_ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
			if (time_ms > offset)
			{
				offset = time_ms;
				break ;
			}
		}
	}
    time_ms -= offset;
	return (time_ms);
}

unsigned long time_has_passed(unsigned long start, unsigned long time)
{
    unsigned long actual;

    actual = get_actual_time_ms();
    if ((actual - start) >= time)
        return (actual);
    return (0);
}