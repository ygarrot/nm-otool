/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:42:36 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/26 18:41:14 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	set_otool(t_otool *otool, void *ptr)
{
	t_mach_header_64			*header64;
	t_mach_header			*header;

	header64 = ptr;
	header = ptr;
	otool->error = 0;
	otool->head.magic = *(unsigned int *)ptr;
	otool->head.ptr = ptr;
	otool->mem.is_big_endian = (otool->head.magic == MH_CIGAM || otool->head.magic == MH_CIGAM_64);
	if (get_int_endian(otool, otool->head.magic) == MH_MAGIC)
	{
		otool->head.cpu_type = get_int_endian(otool, header->cputype);
		otool->head.cpu_subtype = get_int_endian(otool, header->cpusubtype);
	}
	else if (get_int_endian(otool, otool->head.magic == MH_MAGIC_64))
	{
		otool->head.cpu_type = get_int_endian(otool, header64->cputype);
		otool->head.cpu_subtype = get_int_endian(otool, header64->cpusubtype);
	}
}

int		offset_handler(t_otool *otool, void *ptr, int inc_value)
{
if (otool->error == 2)
	{
		otool->error = 0;
		return (1);
	}
	otool->error = (otool->file.offset < ptr + inc_value
			|| (otool->file.offset - ptr + inc_value < 0));
	if (otool->error)
		ft_error(otool->file.name, "truncated or malformed object");
	return (otool->error);
}

t_otool	*get_otool(t_otool *ptr)
{
	static t_otool otool;

	if (ptr)
		otool = *ptr;
	if (!otool.offset_handler)
		otool.offset_handler = offset_handler;
	return (&otool);
}
