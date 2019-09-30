/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 15:06:35 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/09/30 16:09:55 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "malloc.h"

// TODO Combine into one global variable
t_free_block_header	g_tiny = {{BLOCK_TYPE_HEAD, 256, NULL, NULL}, NULL, NULL};
t_free_block_header	g_small = {{BLOCK_TYPE_HEAD, 4096, NULL, NULL}, NULL, NULL};
t_free_block_header	g_large = {{BLOCK_TYPE_HEAD, 0, NULL, NULL}, NULL, NULL};
