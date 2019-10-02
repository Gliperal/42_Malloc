/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:04:35 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/01 21:58:01 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "malloc.h"
#include "free_list.h"
#include "zone.h"

int	is_allocated(void *ptr)
{
	t_block_header *zone_head;
	t_block_header *ptr_block;
	t_block_header		*block;
	int i;

	ptr_block = ft_pointer_sub(ptr, sizeof(t_block_header));
	i = 0;
	while (i < 3)
	{
		zone_head = g_arenas[i].b.next;
		while (zone_head)
		{
			if (ptr_block > zone_head && (void *)ptr_block < ft_pointer_add(zone_head, zone_head->size))
			{
				block = ft_pointer_add(zone_head, sizeof(t_block_header));
				while (block != NULL && block < ptr_block)
					block = block->next;
				return (block != NULL && block->type == BLOCK_TYPE_USED && block == ptr_block);
			}
			zone_head = zone_head->next;
		}
		i++;
	}
	return (0);
}

void	free(void *ptr)
{
	t_block_header		*block;
	t_free_block_header	*neighbor;

	if (!is_allocated(ptr))
		return ;
	block = ft_pointer_sub(ptr, sizeof(t_block_header));
	block->type = BLOCK_TYPE_FREE;
	neighbor = block->next;
	if (neighbor && neighbor->b.type == BLOCK_TYPE_FREE)
	{
		remove_free_block(neighbor);
		merge_consecutive_blocks((t_free_block_header *)block);
	}
	neighbor = block->prev;
	if (neighbor && neighbor->b.type == BLOCK_TYPE_FREE)
	{
		remove_free_block(neighbor);
		merge_consecutive_blocks(neighbor);
		block = (t_block_header *)neighbor;
	}
	if (block->prev == NULL && block->next == NULL)
		zone_free(ft_pointer_sub(block, sizeof(t_block_header)));
	else
		insert_free_block_s((t_free_block_header *)block);
}

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

void	*malloc(size_t size)
{
	t_free_block_header	*arena_head;
	size_t				block_size;
	t_block_header		*block;

	arena_head = get_arena_by_size(size);
	block_size = sizeof(t_block_header) + size;
	if (block_size < sizeof(t_free_block_header))
		block_size = sizeof(t_free_block_header);
	block = (t_block_header *)extract_free_block(arena_head, block_size);
	if (block == NULL)
	{
		block = (t_block_header *)add_new_zone(arena_head, block_size);
		if (block == NULL)
			return (NULL);
	}
	allocate_from_block(block, block_size, arena_head);
	return (block + 1);
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

void	*realloc(void *ptr, size_t size)
{
	t_block_header	*block;
	size_t			new_block_size;
	void			*new;

	if (ptr == NULL)
		return (malloc(size));
	block = ft_pointer_sub(ptr, sizeof(t_block_header));
	new_block_size = size + sizeof(t_block_header);
	if (new_block_size < sizeof(t_free_block_header))
		new_block_size = sizeof(t_free_block_header);
	if (resize_block(block, new_block_size))
		return (ptr);
	new = malloc(size);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, ptr, block->size - sizeof(t_block_header));
	free(ptr);
	return (new);
}
