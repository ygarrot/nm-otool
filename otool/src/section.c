/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 13:25:38 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/04 13:45:39 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include "../../includes/ft_macho.h"

int		is_section_type(t_section *section, char *type)
{
		return (ft_strcmp(section->sectname, type)); 
}

int		is_section64_type(t_section_64	*section64, char *type)
{
		return (ft_strcmp(section64->sectname, type)); 
}

int		is_segment_type(t_section *section, char *type)
{
		return (ft_strcmp(section->segname, type)); 
}

int		is_segment64_type(t_section_64	*section64, char *type)
{
		return (ft_strcmp(section64->segname, type)); 
}

int		is_text_sect(void *sect, unsigned int arch_type)
{
	if (arch_type == MH_MAGIC_64)
		return (!is_section64_type(sect, SECT_TEXT) 
				&& !is_segment64_type(sect, SEG_TEXT));
	return (is_section_type(sect, SECT_TEXT) 
				&& !is_segment_type(sect, SEG_TEXT));
}

