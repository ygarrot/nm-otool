/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:08:01 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/30 17:37:41 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		set_section_addresses(void *ptr,
		void	*struc, uint32_t address)
{
	int index;
	t_section_64	*section;
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


void	cross_command(void *ptr, void *struc, uint32_t index)
{
	t_load_command 				*lc;
	t_symtab_command			*sym;
	t_segment_command_64	*segm;
	t_nm								*nm;

	lc =  ptr;
	nm = struc;
	(void)index;
	if (lc->cmd == LC_SYMTAB)
	{
		sym = (t_symtab_command *)lc;	
		apply_symtab(sym, nm);
			/* nm->string_table = ptr + sym->stroff; */
			/* print_output(sym->nsyms,sym->symoff, nm); */
	}
	if (lc->cmd == LC_SEGMENT_64)
	{
		segm = (struct segment_command_64*)lc;
		iter_over_mem((void*)segm + sizeof(*segm), nm,SECTION_64, &set_section_addresses);
	}
}
