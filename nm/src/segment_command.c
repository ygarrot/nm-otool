/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:08:01 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/25 17:32:43 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		set_section_addresses(void *ptr,
		void	*struc, uint32_t address)
{
	int index;
	t_section	*section;
	t_nm		*nm;

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
	/* ft_printf("%d %d %d %d type %d \n", nm->sect_address[DATA_ADD], */ 
	/* 		nm->sect_address[BSS_ADD], nm->sect_address[TEXT_ADD], index, nm->count_sect); */
	nm->count_sect++;
}

void		set_section_64_addresses(void *ptr,
		void	*struc, uint32_t address)
{
	int index;
	t_section_64	*section;
	t_nm		*nm;

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
	/* ft_printf("%d %d %d type %d \n", nm->sect_address[DATA_ADD], */ 
	/* 		nm->sect_address[BSS_ADD], nm->sect_address[TEXT_ADD], index); */
	nm->count_sect++;
}

void	cross_command(void *ptr, void *struc, uint32_t index)
{
	t_load_command 				*lc;
	int										cmd;
	t_nm								*nm;

	lc =  ptr;
	nm = struc;
	cmd = get_int_endian(nm, lc->cmd);
	(void)index;
	if (cmd == LC_SYMTAB)
	{
		apply_symtab((t_symtab_command*)lc, nm);
	}
	if (cmd == LC_SEGMENT_64)
	{
		iter_over_mem(ptr + sizeof(t_segment_command_64), nm, SECTION_64, &set_section_64_addresses);
	}		
	if (cmd == LC_SEGMENT)
	{
		iter_over_mem(ptr + sizeof(t_segment_command), 
				nm, SECTION, &set_section_addresses);
	}
}
