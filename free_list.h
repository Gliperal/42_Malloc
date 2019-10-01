/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 15:37:26 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/30 16:19:42 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_LIST_H
# define FREE_LIST_H

void				remove_free_block(t_free_block_header *block);
t_free_block_header	*extract_free_block(t_free_block_header *head, size_t size);
void				insert_free_block(t_free_block_header *list,
													t_free_block_header *block);
void				insert_free_block_s(t_free_block_header *free_block);
void				merge_consecutive_free_blocks(t_free_block_header *left);

#endif
