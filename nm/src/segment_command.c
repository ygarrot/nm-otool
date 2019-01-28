/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:08:01 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/27 19:03:24 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		set_section_addresses(void *ptr,
		void *struc, uint32_t address)
{
	t_nm		*nm;
	t_section	*section;
	int			index;

	nm = struc;
	section = ptr;
	index = -1;
	(void)address;
	if (!ft_strcmp(section->segname, SEG_DATA))
	{
		if (!ft_strcmp(section->sectname, SECT_DATA))
			index = DATA_ADD;
		if (!ft_strcmp(section->sectname, SECT_BSS))
			index = BSS_ADD;
	}
	if (!ft_strcmp(section->segname, SEG_TEXT) &&
			!ft_strcmp(section->sectname, SECT_TEXT))
		index = TEXT_ADD;
	if (index != -1)
		nm->sect_address[index] = nm->count_sect;
	nm->count_sect++;
}

void		set_section_64_addresses(void *ptr,
		void *struc, uint32_t address)
{
	t_section_64	*section;
	t_nm			*nm;
	int				index;

	(void)address;
	nm = struc;
	section = ptr;
	index = -1;
	if (!ft_strcmp(section->segname, SEG_DATA))
	{
		if (!ft_strcmp(section->sectname, SECT_DATA))
			index = DATA_ADD;
		if (!ft_strcmp(section->sectname, SECT_BSS))
			index = BSS_ADD;
	}
	if (!ft_strcmp(section->segname, SEG_TEXT) &&
			!ft_strcmp(section->sectname, SECT_TEXT))
		index = TEXT_ADD;
	if (index != -1)
	{
		nm->sect_address[index] = nm->count_sect;
	}
	nm->count_sect++;
}

void		cross_command(void *ptr, void *struc, uint32_t index)
{
	t_load_command		*lc;
	t_nm				*nm;
	int					cmd;

	lc = ptr;
	nm = struc;
	cmd = get_int_endian(nm, lc->cmd);
	(void)index;
	if (cmd == LC_SYMTAB)
	{
		apply_symtab((t_symtab_command*)lc, nm);
	}
	if (cmd == LC_SEGMENT_64)
	{
		iter_over_mem(ptr + sizeof(t_segment_command_64), nm,
				SECTION_64, &set_section_64_addresses);
	}
	if (cmd == LC_SEGMENT)
	{
		iter_over_mem(ptr + sizeof(t_segment_command),
				nm, SECTION, &set_section_addresses);
	}
}
