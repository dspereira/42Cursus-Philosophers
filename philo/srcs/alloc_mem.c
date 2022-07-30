/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 21:04:01 by dsilveri          #+#    #+#             */
/*   Updated: 2022/07/30 22:27:07 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_alloc_mem *alloc_mem(void *data);

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
	while (i < 3)
	{
		if (mem && mem[i].data)
			free(mem[i].data);
		i++;
	}
	if (mem)
		free(mem);
}

static t_alloc_mem *alloc_mem(void *data)
{
	static t_alloc_mem	*mem = 0;
	int					i;

	if (!mem)
	{
		mem = oom_guard2(malloc(3 * sizeof(t_alloc_mem)));
		mem[0].data = 0;
		mem[1].data = 0;
		mem[2].data = 0;
	}
	if (data)
	{
		i = 0;
		while(i < 3)
		{
			if (!mem[i].data)
			{
				mem[i].data = data;
				break ;
			}
			i++;
		}
	}
	return (mem);
}
