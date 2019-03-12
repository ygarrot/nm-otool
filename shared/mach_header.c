/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 10:08:00 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/12 14:36:05 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_macho.h"

int		is_user_arch(t_macho *macho, void *fat_header, int offset)
{
	unsigned int			magic;
	t_mach_header_64		*header64;
	t_mach_header			*header;

	if (macho->offset_handler(macho, fat_header, offset))
		return (1);
	ft_bzero(&macho->mem, sizeof(macho->mem));
	magic = *(unsigned int*)(fat_header + offset);
	header64 = fat_header + offset;
	header = fat_header + offset;
	if (macho->head.no_arch
			|| (magic == MH_MAGIC_64 && header64->cputype == CPU_TYPE_X86_64)
			|| (magic == MH_MAGIC && header->cputype == CPU_TYPE_X86_64))
	{
		cross_arch((void*)fat_header + offset, macho->file.name);
		if (!macho->head.no_arch)
			return (1);
	}
	return (0);
}

void	is_fat_header(void *fat_header, void *struc)
{
	t_fat_arch	*arch;
	t_macho		*macho;
	int			offset;
	int			nfat;

	macho = struc;
	macho->head.active = true;
	if (macho->offset_handler(macho, fat_header, sizeof(t_fat_header)))
		return ;
	arch = (t_fat_arch*)(fat_header + sizeof(t_fat_header));
	nfat = ft_swap_int(((t_fat_header*)fat_header)->nfat_arch);
	while (--nfat >= 0)
	{
		offset = ft_swap_int(arch->offset);
		macho->head.arch_offset = macho->head.ptr + ft_swap_int(arch->size);
		if (is_user_arch(macho, fat_header, offset))
			return ;
		arch++;
	}
	if (macho->head.no_arch)
		return ;
	macho->head.no_arch = true;
	is_fat_header(fat_header, macho);
	macho->head.active = false;
}

void	handle_header64(void *ptr, void *macho)
{
	t_macho				*o;
	t_mach_header_64	*header;

	header = ptr;
	o->mem.iter_nb = get_int_endian(o, header->ncmds);
	iter_over_mem(ptr + sizeof(t_mach_header_64),
	macho, LOAD_COMMAND, &cross_command);
}

void	handle_header32(void *ptr, void *struc)
{
	t_macho					*macho;
	t_mach_header			*header;

	macho = struc;
	header = ptr;
	macho->mem.iter_nb = get_int_endian(macho, header->ncmds);
	iter_over_mem(ptr + sizeof(t_mach_header), macho,
	LOAD_COMMAND, &cross_command);
}
