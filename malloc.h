/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:05:11 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/01 16:28:56 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>

# define NULLPTR 0
# define BLOCK_TYPE_HEAD 42
# define BLOCK_TYPE_FREE 43
# define BLOCK_TYPE_USED 44
# define BLOCK_TYPE_CRUFT 45

typedef struct					s_block_header
{
	size_t						type;
	size_t						size;
	void						*next;
	void						*prev;
}								t_block_header;

typedef struct					s_free_block_header
{
	struct s_block_header		b;
	struct s_free_block_header	*next_free;
	struct s_free_block_header	*prev_free;
}								t_free_block_header;

extern t_free_block_header		g_arenas[];
t_free_block_header				*get_arena_by_size(size_t size);

#endif
