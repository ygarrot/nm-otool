/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:08:01 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/30 14:43:31 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		del_func(void *item)
{
	return ;
}


void		set_section_addresses(void	*ptr,
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

/* void		cross_command(void	*ptr, void	*struc, uint32_t index) */
/* { */
/* 		t_load_command	*lc; */
/* 		t_symtab_command			*sym; */
/* 		t_nm		*nm; */

/* 		nm = struc; */
/* 		(void)index; */
/* 		lc = ptr; */
/* 		if (lc->cmd == LC_SYMTAB) */
/* 		{ */
/* 			sym = (t_symtab_command*)lc; */
/* 			print_output(sym->nsyms,sym->symoff, sym->stroff, ptr, nm); */
/* 		} */
/* 		if (lc->cmd == LC_SEGMENT_64) */
/* 		{ */
/* 			iter_over_mem((t_segment_command_64*)lc,  &nm,SECTION_64, &set_section_addresses); */
/* 		} */
/* } */
