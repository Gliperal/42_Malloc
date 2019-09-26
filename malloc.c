/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:04:35 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/26 16:37:41 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "malloc.h"

# define MALLOC_SIZE_SMALL 256
# define MALLOC_SIZE_LARGE 4096

// TODO Combine into one global variable
t_free_block_header	g_tiny = {{BLOCK_TYPE_HEAD, 256, NULL, NULL}, NULL, NULL};
t_free_block_header	g_small = {{BLOCK_TYPE_HEAD, 4096, NULL, NULL}, NULL, NULL};
t_free_block_header	g_large = {{BLOCK_TYPE_HEAD, 0, NULL, NULL}, NULL, NULL};

void	*zone_new(size_t size, size_t pagesize);
void	*pointer_add(void *ptr, size_t offset);
t_free_block_header	*extract_free_block(t_free_block_header *head, size_t size);
void	insert_free_block(t_free_block_header *list, t_free_block_header *block);

void	my_free(void *ptr)
{
	UNUSED(ptr);
	ft_putstr("free called!\n");
}

void	*todd(size_t size, t_free_block_header *arena_head)
{
	size_t				block_size;
	size_t				zone_size;
	t_block_header		*block;
	t_free_block_header	*free_block;
	t_block_header		*zone_head;

	printf("Mallocing a block of size %lu\n", size);
	block_size = sizeof(t_block_header) + size;
	block = (t_block_header *)extract_free_block(arena_head, block_size);
	if (block == NULL)
	{
		printf("No free block found... allocating a new zone.\n");
		zone_head = (t_block_header *)arena_head;
		while (zone_head->next)
			zone_head = zone_head->next;
		zone_size = (sizeof(t_block_header) + arena_head->b.size) * 100;
		zone_head->next = zone_new(zone_size, getpagesize());
		zone_head = zone_head->next;
		if (zone_head == NULL)
			return NULL;
		free_block = pointer_add(zone_head, sizeof(t_block_header));
		free_block->b.type = BLOCK_TYPE_FREE;
		insert_free_block(arena_head, free_block);
		return todd(size, arena_head);
	}
	printf("Found a free block of size %lu. Using that.\n", block->size);
	if (block->size >= block_size + sizeof(t_free_block_header))
	{
		printf("Block is big enough to split.\n");
		free_block = pointer_add(block, block_size);
		free_block->b.type = BLOCK_TYPE_FREE;
		free_block->b.size = block->size - block_size;
		free_block->b.next = block->next;
		free_block->b.prev = block;
		insert_free_block(arena_head, free_block);
		block->size = block_size;
		block->next = free_block;
		printf("Split into blocks of size %lu and %lu\n", block->size, free_block->b.size);
	}
	block->type = BLOCK_TYPE_USED;
	return (block + 1);
}

void	*my_malloc(size_t size)
{
	if (size < MALLOC_SIZE_SMALL)
		return todd(size, &g_tiny);
	else if (size < MALLOC_SIZE_LARGE)
		return todd(size, &g_small);
	else
		return todd(size, &g_large);
	return 0;
}

void	*my_realloc(void *ptr, size_t size)
{
	UNUSED(ptr);
	UNUSED(size);
	ft_putstr("realloc called!\n");
	return 0;
}

void	show_alloc_mem()
{
	printf("show_alloc_mem\n");
	t_block_header	*zone_head;
	t_block_header	*block;
	size_t			block_size;
	void			*block_end;

	zone_head = g_tiny.b.next;
	while (zone_head != NULL)
	{
		printf("TINY : %p\n", zone_head);
		block = pointer_add(zone_head, sizeof(t_block_header));
		while (block != NULL)
		{
			block_size = block->size - sizeof(t_block_header);
			block_end = pointer_add(block, block_size);
			if (block->type == BLOCK_TYPE_USED)
				printf("%p - %p : %lu bytes\n", block, block_end, block_size);
			block = block->next;
		}
		zone_head = zone_head->next;
	}
	// TODO other arenas
	// TODO total
}
