/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:04:28 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/01 16:29:45 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>

#include "libft/libft.h"

#include "malloc.h"

void				*zone_new(size_t size, size_t pagesize)
{
	size_t			extra;
	void			*zone;
	t_block_header	*zone_header;
	t_block_header	*block_header;

	if (size == 0)
		return (NULL);
	size += sizeof(t_block_header);
	extra = size % pagesize;
	if (extra)
		size += pagesize - extra;
	zone = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (zone == MAP_FAILED)
		return (NULL);
	zone_header = (t_block_header *)zone;
	zone_header->type = BLOCK_TYPE_HEAD;
	zone_header->size = size;
	block_header = ft_pointer_add(zone_header, sizeof(t_block_header));
	block_header->type = BLOCK_TYPE_CRUFT;
	block_header->size = size - sizeof(t_block_header);
	block_header->next = NULL;
	block_header->prev = NULL;
	zone_header->next = NULL;
	zone_header->prev = NULL;
	return (zone);
}

void				zone_free(void *zone)
{
	t_block_header	*zone_header;
	int				status;

	zone_header = (t_block_header *)zone;
	((t_block_header *)zone_header->prev)->next = zone_header->next;
	if (zone_header->next != NULL)
		((t_block_header *)zone_header->next)->prev = zone_header->prev;
	status = munmap(zone, zone_header->size);
	if (status != 0)
		return ;
}

t_free_block_header	*add_new_zone(t_free_block_header *arena_head,
																size_t min_size)
{
	t_block_header		*zone_head;
	size_t				zone_size;
	t_free_block_header	*free_block;

	zone_head = (t_block_header *)arena_head;
	while (zone_head->next)
		zone_head = zone_head->next;
	if (arena_head->b.size > 0)
		zone_size = (sizeof(t_block_header) + arena_head->b.size) * 100;
	else
		zone_size = min_size;
	zone_head->next = zone_new(zone_size, getpagesize());
	if (zone_head->next == NULL)
		return (NULL);
	((t_block_header *)zone_head->next)->prev = zone_head;
	zone_head = zone_head->next;
	free_block = ft_pointer_add(zone_head, sizeof(t_block_header));
	free_block->b.type = BLOCK_TYPE_FREE;
	return (free_block);
}
