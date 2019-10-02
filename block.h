/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 22:13:27 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/01 22:17:07 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_H
# define BLOCK_H

void	allocate_from_block(t_block_header *block, size_t block_size,
											t_free_block_header *arena_head);
int		is_allocated(void *ptr);
int		resize_block(t_block_header *block, size_t new_block_size);

#endif
