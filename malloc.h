/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:05:11 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/25 17:28:33 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define NULLPTR 0
# define BLOCK_TYPE_HEAD 42
# define BLOCK_TYPE_FREE 43
# define BLOCK_TYPE_USED 44

// n = 255
// m = 4095 or 262143

typedef struct	s_block_header
{
	size_t		type;
	size_t		size;
	void		*next;
	void		*prev;
}				t_block_header;

typedef struct				s_free_block_header
{
	struct s_block_header	b;
	void					*next_free;
	void					*prev_free;
}							t_free_block_header;
