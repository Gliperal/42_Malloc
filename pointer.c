/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:04:03 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/26 15:45:18 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*pointer_add(void *ptr, size_t offset)
{
	return ((char *)ptr + offset);
}

void	*pointer_sub(void *ptr, size_t offset)
{
	return ((char *)ptr - offset);
}
