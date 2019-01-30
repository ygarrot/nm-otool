/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:40:41 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/29 11:35:50 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <inttypes.h>

void		set_nm(t_nm *nm, void *ptr)
{
	t_mach_header_64		*header64;
	t_mach_header			*header;

	header64 = ptr;
	header = ptr;
	nm->error = 0;
	btree_erase(&nm->btree, ft_del_nothing_2);
	nm->head.magic = *(unsigned int *)ptr;
	nm->head.ptr = ptr;
	nm->count_sect = 1;
	if (get_int_endian(nm, nm->head.magic) == MH_MAGIC)
	{
		nm->head.cpu_type = get_int_endian(nm, header->cputype);
		nm->head.cpu_subtype = get_int_endian(nm, header->cpusubtype);
	}
	else if (get_int_endian(nm, nm->head.magic == MH_MAGIC_64))
	{
		nm->head.cpu_type = get_int_endian(nm, header64->cputype);
		nm->head.cpu_subtype = get_int_endian(nm, header64->cpusubtype);
	}
}

int			offset_handler(t_nm *nm, void *ptr, int inc_value)
{
	if (nm->error == 2)
	{
		nm->error = 0;
		return (1);
	}
	nm->error = (nm->file.offset < ptr + inc_value
			|| (nm->file.offset - ptr + inc_value < 0));
	if (nm->error)
		ft_error(nm->file.name, "truncated or malformed object");
	return (nm->error);
}

t_nm		*get_nm(t_nm *ptr)
{
	static t_nm		nm;

	if (ptr)
		nm = *ptr;
	if (!nm.offset_handler)
		nm.offset_handler = offset_handler;
	return (&nm);
}

long		get_int_endian(t_nm *nm, long value)
{
	return (nm->mem.is_big_endian ? __builtin_bswap32(value) : value);
}
