/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:17:27 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/01 15:37:33 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "malloc.h"

/*
** Remove a free block from the linked list of free blocks.
*/

void				remove_free_block(t_free_block_header *block)
{
	block->prev_free->next_free = block->next_free;
	if (block->next_free)
		block->next_free->prev_free = block->prev_free;
}

/*
** Search the linked list of free blocks for the smallest block of size at least
** 'size' (assuming the linked list is sorted). Removes that free block from the
** list and returns it. If no block of sufficient size can be found, NULL is
** returned.
*/

t_free_block_header	*extract_free_block(t_free_block_header *head, size_t size)
{
	t_free_block_header	*block;

	block = head->next_free;
	while (block != NULL)
	{
		if (block->b.size >= size)
		{
			remove_free_block(block);
			return (block);
		}
		block = block->next_free;
	}
	return (NULL);
}

/*
** Insert a free block into the linked list of free blocks. insert_free_block
** demands the head of the linked list. insert_free_block_s used to find it
** manually based on the size of neighboring allocated blocks, but that fails
** if realloc changes a block size, so now it backtracks to find the arena head.
*/

void				insert_free_block(t_free_block_header *list,
													t_free_block_header *block)
{
	while (list->next_free && (list->next_free->b.size < block->b.size))
		list = list->next_free;
	block->next_free = list->next_free;
	block->prev_free = list;
	if (list->next_free)
		list->next_free->prev_free = block;
	list->next_free = block;
}

void				insert_free_block_s(t_free_block_header *free_block)
{
	t_block_header		*block;
	t_block_header		*zone;
	t_free_block_header	*arena_head;

	block = (t_block_header *)free_block;
	while (block->prev)
		block = block->prev;
	zone = ft_pointer_sub(block, sizeof(t_block_header));
	while (zone->prev)
		zone = zone->prev;
	arena_head = (t_free_block_header *)zone;
	insert_free_block(arena_head, free_block);
}

/*
** Combine two consecutive blocks into a single larger block. Does not update
** the linked list of free blocks. Does not have to be free blocks.
*/

void				merge_consecutive_blocks(t_free_block_header *left)
{
	t_free_block_header *right;

	right = left->b.next;
	left->b.size += right->b.size;
	left->b.next = right->b.next;
	if (left->b.next != NULL)
		((t_block_header *)left->b.next)->prev = left;
}
