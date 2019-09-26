/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:04:28 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/25 17:40:27 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>	// mmap, munmap
#include <unistd.h>		// getpagesize
#include <stdio.h>		// printf (REMOVE)
#include <string.h>		// strcpy (REMOVE)

#include "malloc.h"

void	*zone_new(size_t size, size_t pagesize)
{
	size_t				extra;
	void				*zone;
	t_block_header		*zone_header;
	t_free_block_header	*block_header;

	if (size == 0)
		return NULL;
	extra = size % pagesize;
	if (extra)
		size += pagesize - size;
	zone = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (zone == MAP_FAILED)
		return NULL;
	zone_header = (t_block_header *)zone;
	zone_header->type = BLOCK_TYPE_HEAD;
	zone_header->size = size;
	block_header = (t_free_block_header *)(zone + sizeof(t_block_header));
	block_header->b.type = BLOCK_TYPE_FREE;
	block_header->b.size = size - sizeof(t_block_header);
	block_header->next_free = NULL;
	block_header->prev_free = NULL;
	return zone;
}

// todo catch double free / bad free exceptions?
void	zone_free(void *zone)
{
	t_block_header	*zone_header;
	int				status;

	zone_header = (t_block_header *)zone;
	status = munmap(zone, zone_header->size);
	if (status != 0)
		printf("It didn't work!\n");
}

int main()
{
	size_t pagesize = getpagesize();
	char *zone = zone_new(420, pagesize);
	if (!zone)
	{
		printf("Failed.\n");
		return 1;
	}
	strcpy(zone + sizeof(t_free_block_header), "Hello world!");
	printf("zone = %p\n", zone);
	printf("zone size = %lu\n", ((t_free_block_header *)zone)->b.size);
	printf("content = %s\n", zone + sizeof(t_free_block_header));
	zone_free(zone);
	zone = NULL;
	return 0;
}
