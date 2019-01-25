/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:08:01 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/25 13:53:18 by ygarrot          ###   ########.fr       */
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
		nm->sect_address[index] = address + 1;
}

void		set_section_64_addresses(void *ptr,
		void	*struc, uint32_t address)
{
	int index;
	static int iter = 1;
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
		nm->sect_address[index] = iter;
	}
	iter++;
}

void	cross_command(void *ptr, void *struc, uint32_t index)
{
	t_load_command 				*lc;
	t_nm								*nm;

	lc =  ptr;
	nm = struc;
	(void)index;
	if (lc->cmd == LC_SYMTAB)
	{
		apply_symtab((t_symtab_command*)lc, nm);
	}
	if (lc->cmd == LC_SEGMENT_64)
	{
		iter_over_mem(ptr + sizeof(t_segment_command_64), nm, SECTION_64, &set_section_64_addresses);
	}		
	if (lc->cmd == LC_SEGMENT)
	{
		iter_over_mem(ptr + sizeof(t_segment_command), 
				nm, SECTION, &set_section_addresses);
	}
}
