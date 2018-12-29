/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:08:01 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/29 16:05:17 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	iter_over_section(t_segment_command_64 *segm, void *struc,
		void	(*f)(t_section_64*, void *struc, uint32_t index))
{
	t_section_64 						*section;
	uint32_t								i;

	i = -1;
	section = (void*) segm + sizeof(*segm);
	while (++i < segm->nsects)
	{
		(*f)(section, struc, i);
		section = (void*)section + sizeof(*section);	
	}
}

void		set_section_addresses(t_section_64 *section,
		void	*ptr, uint32_t address)
{
	int index;
	t_nm		*nm;

	nm = ptr;
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
