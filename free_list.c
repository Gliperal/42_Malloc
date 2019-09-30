/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:17:27 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/30 14:45:05 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_free_block_header	*extract_free_block(t_free_block_header *head, size_t size)
{
	t_free_block_header	*block;

	block = head->next_free;
	while (block != NULL)
	{
		if (block->b.size >= size)
		{
			block->prev_free->next_free = block->next_free;
			if (block->next_free)
				block->next_free->prev_free = block->prev_free;
			return block;
		}
		block = block->next_free;
	}
	return (NULL);
}

void	insert_free_block(t_free_block_header *list, t_free_block_header *block)
{
	while (list->next_free && (list->next_free->b.size < block->b.size))
		list = list->next_free;
	block->next_free = list->next_free;
	block->prev_free = list;
	if (list->next_free)
		list->next_free->prev_free = block;
	list->next_free = block;
}
