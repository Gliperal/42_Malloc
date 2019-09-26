/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:05:11 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/26 15:51:06 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // size_t
#include <stdio.h> // printf (REMOVE)

# define NULLPTR 0
# define BLOCK_TYPE_HEAD 42
# define BLOCK_TYPE_FREE 43
# define BLOCK_TYPE_USED 44
# define BLOCK_TYPE_CRUFT 45

// n = 255
// m = 4095 or 262143

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
