/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 19:57:13 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/30 20:27:16 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*oom_guard(void *p)
{
	if (!p)
	{
		exit(EXIT_FAILURE);
	}
	return (p);
}

int input_args_error(int arg, char *arg_type)
{
    if (arg <= 0)
    {
        ft_putstr_fd("wrong args: ", STDERR_FILENO);
        ft_putstr_fd(arg_type, STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    return (arg);
}
