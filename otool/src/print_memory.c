/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 11:49:33 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/06 13:36:31 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		get_nb_from_map(unsigned char *map, int index, int nb_bytes)
{
	int ret;
	int i;

	ret = 0;
	i = -1;
	while (++i < nb_bytes)
		ret = (ret << 8) | map[index + i];
	return (ret);
}

void	print_classic(unsigned char *ptr, int i)
{
	/* if (!(i%4)) */
	/* 	ft_printf("%0.8x ", *(int*)(ptr + i)); */
			ft_printf("%02x ", ptr[i]);
}

int	otool_format(t_sec section, char *flag)
{
	unsigned int	i;

	i = 0;
	while (i < section.size)
	{
		if (!(i % 16))
		{
			ft_printf(flag,section.addr + i, "        ");
		}
		print_classic(section.ptr, i);
		if (++i && !(i % 16) && i < section.size)
			ft_printf("\n");
	}
	ft_putendl("");
	return (EXIT_SUCCESS);
}

void	print_otool(void *ptr, void *struc, uint32_t index)
{
	t_otool						*otool;
	char 						*flag;

	(void)index;
	otool = struc;
	if (!is_text_sect(ptr, otool->head.magic))
			return ;
	set_section_values(ptr, struc); 
	ft_printf("Contents of (__TEXT,__text) section\n");
	flag = otool->head.magic == MH_MAGIC ? "%08x\t" : "%016llx\t";
	otool_format(otool->section, flag);
}
