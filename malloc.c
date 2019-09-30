/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:04:35 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/30 16:15:29 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "malloc.h"
#include "free_list.h"

void	zone_free(void *zone);
t_free_block_header	*add_new_zone(t_free_block_header *arena_head, size_t min_size);

void	my_free(void *ptr)
{
	t_block_header		*block;
	t_free_block_header	*neighbor;

	ft_printf("Freeing %p\n", ptr);
	block = ft_pointer_sub(ptr, sizeof(t_block_header));
	ft_printf("Block size = %lu\n", block->size);
	block->type = BLOCK_TYPE_FREE;
	neighbor = block->next;
	if (neighbor && neighbor->b.type == BLOCK_TYPE_FREE)
	{
		ft_printf("Found free right neighbor. Merging.\n");
		remove_free_block(neighbor);
		merge_consecutive_free_blocks((t_free_block_header *)block);
	}
	neighbor = block->prev;
	if (neighbor && neighbor->b.type == BLOCK_TYPE_FREE)
	{
		ft_printf("Found free left neighbor. Merging.\n");
		remove_free_block(neighbor);
		merge_consecutive_free_blocks(neighbor);
		block = (t_block_header *)neighbor;
	}
	if (block->prev == NULL && block->next == NULL)
	{
		ft_printf("All blocks freed. Unmapping zone.\n");
		zone_free(ft_pointer_sub(block, sizeof(t_block_header)));
	}
	else
	{
		ft_printf("Freeing done. Inserting free block back into list.\n");
		insert_free_block_s((t_free_block_header *)block);
	}
}

void	*todd(size_t size, t_free_block_header *arena_head)
{
	size_t				block_size;
	t_block_header		*block;
	t_free_block_header	*free_block;

	ft_printf("Mallocing a block of size %lu\n", size);
	block_size = sizeof(t_block_header) + size;
	if (block_size < sizeof(t_free_block_header))
		block_size = sizeof(t_free_block_header);
	block = (t_block_header *)extract_free_block(arena_head, block_size);
	if (block == NULL)
	{
		ft_printf("No free block found... allocating a new zone.\n");
		block = (t_block_header *)add_new_zone(arena_head, block_size);
		if (block == NULL)
			return (NULL);
	}
	ft_printf("Found a free block of size %lu. Using that.\n", block->size);
	if (block->size >= block_size + sizeof(t_free_block_header))
	{
		ft_printf("Block is big enough to split.\n");
		free_block = ft_pointer_add(block, block_size);
		free_block->b.type = BLOCK_TYPE_FREE;
		free_block->b.size = block->size - block_size;
		free_block->b.next = block->next;
		free_block->b.prev = block;
		insert_free_block(arena_head, free_block);
		block->size = block_size;
		block->next = free_block;
		ft_printf("Split into blocks of size %lu and %lu\n", block->size, free_block->b.size);
	}
	block->type = BLOCK_TYPE_USED;
	return (block + 1);
}

void	*my_malloc(size_t size)
{
	if (size < MALLOC_SIZE_SMALL)
		return (todd(size, &g_tiny));
	else if (size < MALLOC_SIZE_LARGE)
		return (todd(size, &g_small));
	else
		return (todd(size, &g_large));
	return (NULL);
}

void	*my_realloc(void *ptr, size_t size)
{
	t_block_header	*block;

	if (ptr == NULL)
		return my_malloc(size);
	block = ft_pointer_sub(ptr, sizeof(t_block_header));
	// If block is already size size, return
	if (block->size >= size + sizeof(t_block_header))
		return (ptr);
	// If sufficient free size to the right, expand block and return
	// If nothing to the right, attempt to expand zone with mmap
	// If all else fails:
	void *new = my_malloc(size);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, ptr, block->size - sizeof(t_block_header));
	my_free(ptr);
	return (new);
}

size_t	show_alloc_zone(const char *name, t_block_header *head);
size_t	show_free_list(t_free_block_header *node);

void	show_alloc_mem(void)
{
	size_t total;

	ft_printf("\n\n");
	ft_printf("show_alloc_mem\n");
	total = 0;
	total += show_alloc_zone("TINY", g_tiny.b.next);
	total += show_alloc_zone("SMALL", g_small.b.next);
	total += show_alloc_zone("LARGE", g_large.b.next);
	ft_printf("Total : %lu bytes\n", total);
	ft_printf("------------------------------\nFREE :\n");
	total = 0;
	total += show_free_list(g_tiny.next_free);
	total += show_free_list(g_small.next_free);
	total += show_free_list(g_large.next_free);
	ft_printf("Total : %lu bytes\n", total);
	ft_printf("\n\n");
}
