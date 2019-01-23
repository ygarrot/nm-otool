/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:51:55 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/23 19:00:08 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"
#include <stdio.h>
#include <inttypes.h>

long		get_int_indian(t_otool *otool, long value)
{
	return value;
	return otool->mem.is_big_endian ? __builtin_bswap32(value) : value;
}
