/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:42:36 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/04 15:25:08 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		offset_handler(t_otool *otool, void *ptr, int inc_value)
{
	/* ft_printf("%lld %lld \n", otool->offset, ptr + inc_value); */
	return (otool->offset > ptr + inc_value);
}

t_otool		*get_otool(t_otool *ptr)
{
		static t_otool otool;

		if (ptr)
			otool = *ptr;
		if (!otool.offset_handler)
			otool.offset_handler = offset_handler;
		return (&otool);
}
