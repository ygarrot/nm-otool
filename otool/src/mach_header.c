/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 10:08:00 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/28 18:01:49 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		is_user_arch(t_otool *otool, void *fat_header, int offset)
{
	unsigned int			magic;
	t_mach_header_64		*header64;
	t_mach_header			*header;

	if (otool->offset_handler(otool, fat_header, offset))
		return (1);
	ft_bzero(&otool->mem, sizeof(otool->mem));
	magic = *(unsigned int*)(fat_header + offset);
	header64 = fat_header + offset;
	header = fat_header + offset;
	if (otool->head.no_arch
			|| (magic == MH_MAGIC_64 && header64->cputype == CPU_TYPE_X86_64)
			|| (magic == MH_MAGIC && header->cputype == CPU_TYPE_X86_64))
	{
		cross_arch((void*)fat_header + offset, otool->file.name);
		if (!otool->head.no_arch)
			return (1);
	}
	return (0);
}

void	is_fat_header(void *fat_header, void *struc)
{
	t_fat_arch	*arch;
	t_otool		*otool;
	int			offset;
	int			nfat;

	otool = struc;
	otool->head.active = true;
	if (otool->offset_handler(otool, fat_header, sizeof(t_fat_header)))
		return ;
	arch = (t_fat_arch*)(fat_header + sizeof(t_fat_header));
	nfat = ft_swap_int(((t_fat_header*)fat_header)->nfat_arch);
	while (--nfat >= 0)
	{
		offset = ft_swap_int(arch->offset);
		otool->head.arch_offset = otool->head.ptr + ft_swap_int(arch->size);
		if (is_user_arch(otool, fat_header, offset))
			return ;
		arch++;
	}
	if (otool->head.no_arch)
		return ;
	otool->head.no_arch = true;
	is_fat_header(fat_header, otool);
	otool->head.active = false;
}

void	handle_header64(void *ptr, void *otool)
{
	t_otool				*o;
	t_mach_header_64	*header;

	o = otool;
	header = ptr;
	o->mem.iter_nb = get_int_endian(o, header->ncmds);
	iter_over_mem(ptr + sizeof(t_mach_header_64),
	otool, LOAD_COMMAND, &cross_command);
}

void	handle_header32(void *ptr, void *otool)
{
	t_otool					*o;
	t_mach_header			*header;

	o = otool;
	header = ptr;
	o->mem.iter_nb = get_int_endian(o, header->ncmds);
	iter_over_mem(ptr + sizeof(t_mach_header), otool,
	LOAD_COMMAND, &cross_command);
}
