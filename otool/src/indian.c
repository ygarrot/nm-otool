/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:51:55 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/23 16:44:14 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		get_int_indian(t_otool *otool, int value)
{
	return otool->mem.is_big_endian ? ft_swap_int(value) : value;
}
