/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 21:04:01 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/02 12:28:43 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define MAX_MEM_ALLOC	5

static t_alloc_mem	*alloc_mem(void *data);

void	init_alloc_mem(void)
{
	alloc_mem(0);
}

void	save_alloc_mem(void *data)
{
	alloc_mem(data);
}

void	free_alloc_mem(void)
{
	t_alloc_mem	*mem;
	int			i;

	mem = alloc_mem(0);
	i = 0;
	while (i < MAX_MEM_ALLOC)
	{
		if (mem && mem[i].data)
			free(mem[i].data);
		i++;
	}
	if (mem)
		free(mem);
}

static t_alloc_mem	*alloc_mem(void *data)
{
	static t_alloc_mem	*mem = 0;
	int					i;

	if (!mem)
	{
		mem = oom_guard2(malloc(MAX_MEM_ALLOC * sizeof(t_alloc_mem)));
		i = -1;
		while (++i < MAX_MEM_ALLOC)
			mem[i].data = 0;
	}
	if (data)
	{
		i = -1;
		while (++i < MAX_MEM_ALLOC)
		{
			if (!mem[i].data)
			{
				mem[i].data = data;
				break ;
			}
		}
	}
	return (mem);
}
