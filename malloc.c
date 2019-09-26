/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:04:35 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/25 15:07:46 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	free(void *ptr)
{
	UNUSED(ptr);
	ft_putstr("free called!\n");
}

void	*malloc(size_t size)
{
	UNUSED(size);
	ft_putstr("malloc called!\n");
	return 0;
}

void	*realloc(void *ptr, size_t size)
{
	UNUSED(ptr);
	UNUSED(size);
	ft_putstr("realloc called!\n");
	return 0;
}

void	show_alloc_mem()
{
}
