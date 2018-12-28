/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:08:01 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/28 17:09:02 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	iter_over_section(t_segment_command_64 *segm, void	*struc,
		void	(*f)(t_section_64, void*))
{
	t_section_64 						*section;
	uint32_t								i;

	i = -1;
	section = (void*) segm + sizeof(*segm);
	while (++i < segm->nsects)
	{
		if (ft_strcmp(segm->segname, SEG_DATA))
			ft_printf("section name: %s\n", section->sectname);
		ft_printf("section count %#x\n", count);
		count++;
		(*f)(section, struc, count);
		section = (void*)section + sizeof(*section);	
	}
}

void		set_section_addresses(t_section_64 *section, void	*nm)
{
	if (!ft_strncmp(section->segname, SEG_DATA))
	{
			if (!ft_strncmp(section->sectname, SECT_DATA))	
				nm->sect_address[DATA_ADD] = nm->count_sect;
			if (!ft_strncmp(section->sectname, SECT_BSS))
				nm->sect_address[BSS_ADD] = nm->count_sect;
	}
	if (!ft_strncmp(section->segname, SEG_TEXT) &&
			!ft_strncmp(section->sectname, SECT_TEXT))
		nm->sect_address[TEXT_ADD] = nm->count_sect;
	nm->count_sect++;
}
