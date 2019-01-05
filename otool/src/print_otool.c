/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_otool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 12:47:14 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/05 14:21:18 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		get_section_offset(void *ptr, t_otool *otool)
{
	t_section_64 *test;

	test = ptr;
	if (otool->magic_number == MH_MAGIC_64)
		return (test->offset);
	else
		return (((t_section*)ptr)->offset);
}

void		set_section_values(void *ptr, t_otool *otool)
{
	t_section_64		*section_64;
	t_section				*section;

	section_64 = ptr;
	section = ptr;

	if (otool->magic_number == MH_MAGIC_64)
		otool->section = (t_sec){ .size = section_64->size, .ptr =  otool->header + section_64->offset, .addr = section_64->addr};
	else
	{
		otool->section = (t_sec){ .size = section->size, .ptr =  otool->header + section->offset, .addr = section->addr};
	}	
}

void	print_otool(void *ptr, void *struc, uint32_t index)
{
	uintmax_t								i;
	t_otool						*otool;
	char 						*flag;

	(void)index;
	otool = struc;
	if (!is_text_sect(ptr, otool->magic_number))
			return ;
	set_section_values(ptr, struc); 
	i = 0;
	ft_printf("Contents of (__TEXT,__text) section\n");
	flag = otool->magic_number == MH_MAGIC ? "%08x\t" : "%016llx\t";
	while (i < otool->section.size)
	{
		if (!(i % 16))
			ft_printf(flag,otool->section.addr + i, "        ");
		ft_printf("%02x ", otool->section.ptr[i]);
		if (++i && !(i % 16) && i < otool->section.size)
			ft_printf("\n");
	}
	ft_putendl("");
}

void	cross_command(void *ptr, void *struc, uint32_t index)
{
	t_load_command 				*lc;

	lc =  ptr;
	(void)index;
	int tes = lc->cmd;

	if (tes == LC_SEGMENT_64)
	{
		iter_over_mem(ptr + sizeof(t_segment_command_64), struc, SECTION_64, &print_otool);
	}
	if (lc->cmd == LC_SEGMENT)
	{
		iter_over_mem(ptr + sizeof(t_segment_command), 
				struc, SECTION, &print_otool);
	}
}
