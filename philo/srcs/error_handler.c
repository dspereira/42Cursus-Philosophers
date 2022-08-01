/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 19:57:13 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/31 23:18:05 by dsilveri         ###   ########.fr       */
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
        ft_putstr_fd("Wrong args: ", STDERR_FILENO);
        ft_putstr_fd(arg_type, STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    return (arg);
}

void number_input_args_error(int argc)
{
    if (argc < 5 || argc > 6)
    {
        ft_putstr_fd("Wrong number of args \n", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
}

// precisa de limpar os mutex 
// pthread_detach
void thread_error(int err, char *type_error)
{
    if (err)
    {
        free_alloc_mem();
        ft_putstr_fd(type_error, STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
}