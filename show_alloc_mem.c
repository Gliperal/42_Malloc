/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:35:04 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/01 16:20:48 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

#include "malloc.h"

size_t	show_alloc_block(t_block_header *block, int verbose)
{
	void	*block_start;
	void	*block_end;
	size_t	block_size;

	block_start = ft_pointer_add(block, sizeof(t_block_header));
	block_size = block->size - sizeof(t_block_header);
	block_end = ft_pointer_add(block, block->size);
	if (block->type == BLOCK_TYPE_USED)
	{
		ft_printf("%s%p - %p : %lu bytes\n", verbose ? "(USED) " : "",
											block_start, block_end, block_size);
		return (block_size);
	}
	else if (verbose && block->type == BLOCK_TYPE_FREE)
		ft_printf("(FREE) %p : %lu bytes\n", block_start, block->size);
	return (0);
}

size_t	show_alloc_zone(const char *name, t_block_header *head, int verbose)
{
	t_block_header	*block;
	size_t			total_size;

	total_size = 0;
	while (head != NULL)
	{
		ft_printf("%s : %p\n", name, head);
		block = ft_pointer_add(head, sizeof(t_block_header));
		while (block != NULL)
		{
			total_size += show_alloc_block(block, verbose);
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
		ft_printf("%p : %lu bytes\n", node, node->b.size);
		total_size += node->b.size;
		node = node->next_free;
	}
	return (total_size);
}

void	show_alloc_mem(void)
{
	size_t	total;

	total = 0;
	total += show_alloc_zone("TINY", g_arenas[0].b.next, 0);
	total += show_alloc_zone("SMALL", g_arenas[1].b.next, 0);
	total += show_alloc_zone("LARGE", g_arenas[2].b.next, 0);
	ft_printf("Total : %lu bytes\n", total);
}

void	show_alloc_mem_ex(void)
{
	size_t total;

	ft_putstr("\n\n");
	ft_putstr("show_alloc_mem\n");
	total = 0;
	total += show_alloc_zone("TINY", g_arenas[0].b.next, 1);
	total += show_alloc_zone("SMALL", g_arenas[1].b.next, 1);
	total += show_alloc_zone("LARGE", g_arenas[2].b.next, 1);
	ft_printf("Total : %lu bytes\n", total);
	ft_putstr("------------------------------\nFREE :\n");
	total = 0;
	total += show_free_list(g_arenas[0].next_free);
	total += show_free_list(g_arenas[1].next_free);
	total += show_free_list(g_arenas[2].next_free);
	ft_printf("Total : %lu bytes\n", total);
	ft_putstr("\n\n");
}
