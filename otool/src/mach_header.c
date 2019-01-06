/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 10:08:00 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/06 17:00:11 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"


void	is_fat_header(void *fat_header, void *struc)
{
	int		offset;
	int		nfat;
	t_otool		*otool;
	t_fat_arch *arch;

	otool = struc;
	arch = (t_fat_arch*)(fat_header + sizeof(t_fat_header));
	nfat = ft_swap_int(((t_fat_header*)fat_header)->nfat_arch);
	while (--nfat >= 0)
	{
		offset = ft_swap_int(arch->offset);
		unsigned int magic = *(unsigned int*)(fat_header + offset); 
		if (otool->head.no_arch
				|| (magic == MH_MAGIC_64 && 
						((t_mach_header_64*)((void*)fat_header + offset))->cputype == CPU_TYPE_X86_64)
	|| (magic == MH_MAGIC &&  
						((t_mach_header*)((void*)fat_header + offset))->cputype == CPU_TYPE_X86_64))
		{	
			cross_arch((void*)fat_header + offset, 0);
			if (!otool->head.no_arch)
				return ;
		}
		arch++;
	}
	if (otool->head.no_arch)
		return;
	otool->head.no_arch = 1;
	is_fat_header(fat_header, otool);
}

void	handle_header64(void *ptr, void *otool)
{
	t_otool						*o;
	t_mach_header_64	*header;

	o = otool;
	header = ptr;
	o->mem.iter_nb = header->ncmds;
	o->head.cputype = header->cputype; 
	iter_over_mem(ptr + sizeof(t_mach_header_64), otool, LOAD_COMMAND, &cross_command);  
}

void	handle_header32(void *ptr, void *otool)
{
	t_otool						*o;
	t_mach_header			*header;

	o = otool;
	header = ptr;
	o->mem.iter_nb = header->ncmds;
	o->head.cputype = header->cputype; 
	iter_over_mem(ptr + sizeof(t_mach_header), otool, LOAD_COMMAND, &cross_command);
}
