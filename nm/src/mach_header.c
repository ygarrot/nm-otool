/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 10:08:00 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/26 13:06:41 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		is_user_arch(t_nm *nm, void *fat_header, int offset)
{
	unsigned int			magic;
	t_mach_header_64		*header64;
	t_mach_header			*header;

	magic = *(unsigned int*)(fat_header + offset);
	header64 = fat_header + offset;
	header = fat_header + offset;
	if (nm->head.no_arch
			|| (magic == MH_MAGIC_64 && header64->cputype == CPU_TYPE_X86_64)
			|| (magic == MH_MAGIC && header->cputype == CPU_TYPE_X86_64))
	{
		nm->count_sect = 1;
		cross_arch((void*)fat_header + offset, nm->file.name);
		/* btree_erase(&nm->btree, ft_del_nothing_2); */
		if (!nm->head.no_arch)
			return (1);
	}
	return (0);
}

void	is_fat_header(void *fat_header, void *struc)
{
	t_fat_arch	*arch;
	t_nm		*nm;
	int			offset;
	int			nfat;

	nm = struc;
	if (nm->offset_handler(nm, fat_header, sizeof(t_fat_header)))
		return ;
	arch = (t_fat_arch*)(fat_header + sizeof(t_fat_header));
	nfat = ft_swap_int(((t_fat_header*)fat_header)->nfat_arch);
	while (--nfat >= 0)
	{
		ft_bzero(&nm->mem, sizeof(nm->mem));
		offset = ft_swap_int(arch->offset);
		if (nm->offset_handler(nm, fat_header, offset))
			return ;
		if (is_user_arch(nm, fat_header, offset))
			return ;
		arch++;
	}
	if (nm->head.no_arch)
		return ;
	nm->head.no_arch = true;
	is_fat_header(fat_header, nm);
}

void	handle_header64(void *ptr, void *nm)
{
	t_nm				*o;
	t_mach_header_64	*header;

	o = nm;
	header = ptr;
	o->mem.iter_nb = get_int_endian(o, header->ncmds);
	o->head.cputype = get_int_endian(o, header->cputype);
	iter_over_mem(ptr + sizeof(t_mach_header_64),
	nm, LOAD_COMMAND, &cross_command);
}

void	handle_header32(void *ptr, void *nm)
{
	t_nm					*o;
	t_mach_header			*header;

	o = nm;
	header = ptr;
	o->mem.iter_nb = get_int_endian(o, header->ncmds);
	o->head.cputype = get_int_endian(o, header->cputype);
	iter_over_mem(ptr + sizeof(t_mach_header), nm,
	LOAD_COMMAND, &cross_command);
}
