/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:08:01 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/29 14:58:03 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	iter_over_section(t_segment_command_64 *segm, void	*struc,
		void	(*f)(t_section_64*, t_nm *struc))
{
	t_section_64 						*section;
	uint32_t								i;

	i = -1;
	section = (void*) segm + sizeof(*segm);
	while (++i < segm->nsects)
	{
		(*f)(section, struc);
		section = (void*)section + sizeof(*section);	
	}
}

void		set_section_addresses(t_section_64 *section, t_nm	*nm)
{
	ft_printf("%d\n", nm->count_sect);
	nm->count_sect++;
	if (!ft_strcmp(section->segname, SEG_DATA))
	{
			if (!ft_strcmp(section->sectname, SECT_DATA))	
				nm->sect_address[DATA_ADD] = nm->count_sect;
			if (!ft_strcmp(section->sectname, SECT_BSS))
				nm->sect_address[BSS_ADD] = nm->count_sect;
	}
	if (!ft_strcmp(section->segname, SEG_TEXT) &&
			!ft_strcmp(section->sectname, SECT_TEXT))
		nm->sect_address[TEXT_ADD] = nm->count_sect;
}
