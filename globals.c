/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 15:06:35 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/01 15:45:42 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "malloc.h"

t_free_block_header	g_arenas[] = {
	{{BLOCK_TYPE_HEAD, 256, NULL, NULL}, NULL, NULL},
	{{BLOCK_TYPE_HEAD, 4096, NULL, NULL}, NULL, NULL},
	{{BLOCK_TYPE_HEAD, 0, NULL, NULL}, NULL, NULL}
};

t_free_block_header	*get_arena_by_size(size_t size)
{
	int i;

	i = 0;
	while (1)
	{
		if (size < g_arenas[i].b.size || 0 == g_arenas[i].b.size)
			return (g_arenas + i);
		i++;
	}
}
