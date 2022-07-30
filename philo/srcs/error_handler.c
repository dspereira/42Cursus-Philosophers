/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 19:57:13 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/30 22:30:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*oom_guard(void *p)
{
	if (!p)
	{
        free_alloc_mem();
        ft_putstr_fd("Out of memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (p);
}

void	*oom_guard2(void *p)
{
	if (!p)
	{
        ft_putstr_fd("Out of memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (p);
}

int input_args_error(int arg, char *arg_type)
{
    if (arg <= 0)
    {
        free_alloc_mem();
        ft_putstr_fd("wrong args: ", STDERR_FILENO);
        ft_putstr_fd(arg_type, STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    return (arg);
}
