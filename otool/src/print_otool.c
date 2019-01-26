/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_otool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 12:47:14 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/26 18:41:14 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		get_section_offset(void *ptr, t_otool *otool)
{
	t_section_64	*section;

	if (!ptr || !otool)
		return (0);
	section = ptr;
	if (otool->head.magic == MH_MAGIC_64)
		return (section->offset);
	else
		return (((t_section*)ptr)->offset);
}

void	set_section_values(void *ptr, t_otool *otool)
{
	t_section_64		*section_64;
	t_section			*section;

	section_64 = ptr;
	section = ptr;
	if (!ptr || !otool)
		return ;
	if (otool->head.magic == MH_MAGIC_64 || otool->head.magic == MH_CIGAM_64)
		otool->section = (t_sec){
		.size = get_int_endian(otool, section_64->size),
		.ptr = otool->head.ptr + get_int_endian(otool, section_64->offset),
		.addr = section_64->addr};
	else
	{
		otool->section = (t_sec){
		.size = get_int_endian(otool, section->size),
		.ptr = otool->head.ptr + get_int_endian(otool, section->offset),
		.addr = section->addr};
	}
}

void	cross_command(void *ptr, void *struc, uint32_t index)
{
	t_load_command		*lc;
	int					cmd;

	(void)index;
	if (!ptr || !struc)
		return ;
	lc = ptr;
	cmd = get_int_endian(struc, lc->cmd);
	if (cmd == LC_SEGMENT_64)
	{
		iter_over_mem(ptr + sizeof(t_segment_command_64),
				struc, SECTION_64, &print_otool);
	}
	else if (cmd == LC_SEGMENT)
	{
		iter_over_mem(ptr + sizeof(t_segment_command),
				struc, SECTION, &print_otool);
	}
}
