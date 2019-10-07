/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:04:35 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/06 20:25:28 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "malloc.h"
#include "free_list.h"
#include "zone.h"
#include "block.h"

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

void	*realloc(void *ptr, size_t size)
{
	t_block_header	*block;
	size_t			new_block_size;
	void			*new;

	if (ptr == NULL)
		return (malloc(size));
	if (!is_allocated(ptr))
		return (NULL);
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
