/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:35:04 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/26 18:36:35 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*pointer_add(void *ptr, size_t offset);

size_t	show_alloc_zone(const char *name, t_block_header *head)
{
	t_block_header	*block;
	void			*block_start;
	void			*block_end;
	size_t			block_size;
	size_t			total_size;

	total_size = 0;
	while (head != NULL)
	{
		printf("%s : %p\n", name, head);
		block = pointer_add(head, sizeof(t_block_header));
		while (block != NULL)
		{
			block_start = pointer_add(block, sizeof(t_block_header));
			block_end = pointer_add(block, block_size);
			block_size = block->size - sizeof(t_block_header);
			if (block->type == BLOCK_TYPE_USED)
			{
				printf("(USED) %p - %p : %lu bytes\n", block_start, block_end, block_size);
				total_size += block_size;
			}
			else if (block->type == BLOCK_TYPE_FREE)
				printf("(FREE) %p : %lu bytes\n", block_start, block->size);
			block = block->next;
		}
		head = head->next;
	}
	return (total_size);
}

size_t	show_free_list(t_free_block_header *node)
{
	size_t total_size;

	total_size = 0;
	while (node != NULL)
	{
		printf("%p : %lu bytes\n", node, node->b.size);
		total_size += node->b.size;
		node = node->next_free;
	}
	return (total_size);
}
