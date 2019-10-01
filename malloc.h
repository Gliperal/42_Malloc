/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:05:11 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/01 15:52:13 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h> // size_t

# define NULLPTR 0
# define BLOCK_TYPE_HEAD 42
# define BLOCK_TYPE_FREE 43
# define BLOCK_TYPE_USED 44
# define BLOCK_TYPE_CRUFT 45

// TODO play around with these values
//# define MALLOC_SIZE_SMALL 256
//# define MALLOC_SIZE_LARGE 4096

typedef struct	s_block_header
{
	size_t		type;
	size_t		size;
	void		*next;
	void		*prev;
}				t_block_header;

typedef struct					s_free_block_header
{
	struct s_block_header		b;
	struct s_free_block_header	*next_free;
	struct s_free_block_header	*prev_free;
}								t_free_block_header;

extern t_free_block_header	g_arenas[];
t_free_block_header			*get_arena_by_size(size_t size);

#endif
