/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_otool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 12:47:14 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/02 11:49:32 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		is_text_sect(void *sect, t_otool *struc)
{
	t_section_64		*section_64;
	t_section		*section;

	section_64 = sect;
	section = sect;
	if (struc->magic_number == MH_MAGIC_64)
	{
		if (!ft_strcmp(section_64->sectname, SECT_TEXT) 
			&& !ft_strcmp(section_64->segname, SEG_TEXT)) 
		return (1);
	}
	else 
	{
		if (!ft_strcmp(section->sectname, SECT_TEXT) 
			&& !ft_strcmp(section->segname, SEG_TEXT)) 
			return (1);
	}
	return (0);
}
int		get_section_offset(void *ptr, t_otool *otool)
{
	t_section_64 *test;

	test = ptr;
	if (otool->magic_number == MH_MAGIC_64)
		return (test->offset);
	else
		return (((t_section*)ptr)->offset);
}

void	print_otool(void *ptr, void *struc, uint32_t index)
{
	uint32_t		i;
	unsigned char		*mem;
	t_section_64 *section;

	(void)index;
	section = ptr;
	t_otool *otool = struc;
	if (!is_text_sect(ptr, struc))
			return ;
	mem = otool->header + section->offset;
	/* mem = otool->header + get_section_offset(ptr, struc); */
	otool = struc;
	i = 0;
	ft_printf("Contents of (__TEXT,__text) section\n");
	char *flag = otool->magic_number == MH_MAGIC ? "%08x%s" : "%016llx%s";
	while (i < section->size)
	{
		int	i2 = -1;
		ft_printf(flag,section->offset + i, "         ");
		while (++i2 < 16)
			ft_printf("%02x ", mem[i2]);
		ft_printf("\n");
		mem +=16;
		i+=16;
	}
}

void	cross_command(void *ptr, void *struc, uint32_t index)
{
	t_load_command 				*lc;

	lc =  ptr;
	(void)index;
	if (lc->cmd == LC_SEGMENT_64)
		iter_over_mem(ptr + sizeof(t_segment_command_64), struc, SECTION_64, &print_otool);
	if (lc->cmd == LC_SEGMENT)
	{
		iter_over_mem(ptr + sizeof(t_segment_command), 
				struc, SECTION, &print_otool);
	}
}
