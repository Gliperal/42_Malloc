/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:25:24 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/10/01 15:25:52 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZONE_H
# define ZONE_H

void				zone_free(void *zone);
t_free_block_header	*add_new_zone(t_free_block_header *arena_head,
															size_t min_size);

#endif
