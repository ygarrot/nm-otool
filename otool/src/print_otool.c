/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_otool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 12:47:14 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/02 13:42:01 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		is_text_sect(void *sect, t_otool *struc)
{
	t_section_64		*section_64;
	t_section		*section;

	section_64 = sect;
	section = sect;
	if (struc->magic_number == MH_MAGIC_64)
	{
		if (!ft_strcmp(section_64->sectname, SECT_TEXT) 
			&& !ft_strcmp(section_64->segname, SEG_TEXT)) 
		return (1);
	}
	else 
	{
		if (!ft_strcmp(section->sectname, SECT_TEXT) 
			&& !ft_strcmp(section->segname, SEG_TEXT)) 
			return (1);
	}
	return (0);
}
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
	t_sec						*o_section;

	o_section = &otool->section;
	if (otool->magic_number == MH_MAGIC_64)
	{
		section_64 = ptr;
		o_section->size = section_64->size;
		o_section->ptr = otool->header + section_64->offset;
		o_section->addr = section_64->addr;
	}
	else
	{	
		section = ptr;
		/* .o_section = { .size = .section->size, .ptr =  otool->header + section->offset, .add = section->addr}; */
		o_section->size = section->size;
		o_section->ptr = otool->header + section->offset;
		o_section->addr = section->addr;
	}
}

void	print_otool(void *ptr, void *struc, uint32_t index)
{
	int								i;
	t_otool						*otool;

	(void)index;
	if (!is_text_sect(ptr, struc))
			return ;
	set_section_values(ptr, struc); 
	otool = struc;
	i = 0;
	ft_printf("Contents of (__TEXT,__text) section\n");
	char *flag = otool->magic_number == MH_MAGIC ? "%08x%s" : "%016llx%s";
	while (i < otool->section.size)
	{
		if (!(i%16))
			ft_printf(flag,otool->section.addr + i, "        ");
		ft_printf("%02x ", otool->section.ptr[i]);
		i++;
		if (i && !(i%16))
			ft_printf("\n");
	}
}

void	cross_command(void *ptr, void *struc, uint32_t index)
{
	t_load_command 				*lc;

	lc =  ptr;
	(void)index;
	if (lc->cmd == LC_SEGMENT_64)
	{
		iter_over_mem(ptr + sizeof(t_segment_command_64), struc, SECTION_64, &print_otool);
	}
	if (lc->cmd == LC_SEGMENT)
	{
		iter_over_mem(ptr + sizeof(t_segment_command), 
				struc, SECTION, &print_otool);
	}
}
