/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_otool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 12:47:14 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/24 14:35:03 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		get_section_offset(void *ptr, t_otool *otool)
{
	t_section_64 *test;

	if (!ptr || !otool)
		return (0);
	test = ptr;
	if (otool->head.magic == MH_MAGIC_64)
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
	if (!ptr || !otool)
		return;
	if ( otool->head.magic == MH_MAGIC_64 || otool->head.magic == MH_CIGAM_64)
		otool->section = (t_sec){ .size = get_int_indian(otool, section_64->size), .ptr =  otool->head.ptr + get_int_indian(otool, section_64->offset), .addr = section_64->addr};
	else
	{
		otool->section = (t_sec){ .size = get_int_indian(otool, section->size), .ptr =  otool->head.ptr + get_int_indian(otool, section->offset), .addr = section->addr};
	}	
}

void	cross_command(void *ptr, void *struc, uint32_t index)
{
	t_load_command 				*lc;

	(void)index;
	if (!ptr || !struc)
		return;
	lc =  ptr;
	int tes = get_int_indian(struc, lc->cmd);
	if (tes == LC_SEGMENT_64)
	{
		iter_over_mem(ptr + sizeof(t_segment_command_64), struc, SECTION_64, &print_otool);
	}
	else if (tes == LC_SEGMENT)
	{
		iter_over_mem(ptr + sizeof(t_segment_command), 
				struc, SECTION, &print_otool);
	}
}
