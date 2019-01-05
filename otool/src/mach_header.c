/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 10:08:00 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/05 11:00:36 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"


void	is_fat_header(void *fat_header, void *otool)
{
	int		offset;
	int		nfat;
	t_fat_arch *arch;

	(void)otool;
	arch = (t_fat_arch*)(fat_header + 1);
	nfat = ft_swap_int(((t_fat_header*)fat_header)->nfat_arch);
	while (--nfat >= 0)
	{
		offset = ft_swap_int(arch->offset);
		cross_arch((void*)fat_header + offset);
		return ;
		arch++;
	}
}

void	handle_header64(void *ptr, void *otool)
{
		((t_otool*)otool)->iter_nb = ((t_mach_header_64*)ptr)->ncmds;
		iter_over_mem(ptr + sizeof(t_mach_header_64), otool, LOAD_COMMAND, &cross_command);  
}

void	handle_header32(void *ptr, void *otool)
{
		((t_otool*)otool)->iter_nb = ((t_mach_header*)ptr)->ncmds;
		iter_over_mem(ptr + sizeof(t_mach_header), otool, LOAD_COMMAND, &cross_command);
}
