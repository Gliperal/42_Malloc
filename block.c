/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 22:11:52 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/01 22:16:30 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "malloc.h"
#include "free_list.h"

void	allocate_from_block(t_block_header *block, size_t block_size,
												t_free_block_header *arena_head)
{
	t_free_block_header	*free_block;

	if (block->size >= block_size + sizeof(t_free_block_header))
	{
		free_block = ft_pointer_add(block, block_size);
		free_block->b.type = BLOCK_TYPE_FREE;
		free_block->b.size = block->size - block_size;
		free_block->b.next = block->next;
		free_block->b.prev = block;
		if (arena_head == NULL)
			insert_free_block_s(free_block);
		else
			insert_free_block(arena_head, free_block);
		block->size = block_size;
		block->next = free_block;
	}
	block->type = BLOCK_TYPE_USED;
}

int		is_allocated(void *ptr)
{
	t_block_header	*zone_head;
	t_block_header	*ptr_block;
	t_block_header	*block;
	int				i;

	ptr_block = ft_pointer_sub(ptr, sizeof(t_block_header));
	i = 0;
	while (i < 3)
	{
		zone_head = g_arenas[i].b.next;
		while (zone_head)
		{
			if (ptr_block > zone_head && (void *)ptr_block
								< ft_pointer_add(zone_head, zone_head->size))
			{
				block = ft_pointer_add(zone_head, sizeof(t_block_header));
				while (block != NULL && block != ptr_block)
					block = block->next;
				return (block != NULL && block->type == BLOCK_TYPE_USED);
			}
			zone_head = zone_head->next;
		}
		i++;
	}
	return (0);
}

/*
** The use of MAP_FIXED in mmap is discouraged, so I'm choosing not to attempt
** to expand mmap mappings.
*/

int		resize_block(t_block_header *block, size_t new_block_size)
{
	t_free_block_header *neighbor;

	if (block->size >= new_block_size)
		return (1);
	neighbor = block->next;
	if (neighbor != NULL
			&& neighbor->b.type == BLOCK_TYPE_FREE
			&& block->size + neighbor->b.size >= new_block_size)
	{
		remove_free_block(neighbor);
		merge_consecutive_blocks((t_free_block_header *)block);
		allocate_from_block(block, new_block_size, NULL);
		return (1);
	}
	return (0);
}
