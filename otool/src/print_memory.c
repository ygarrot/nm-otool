/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 11:49:33 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/23 18:56:29 by ygarrot          ###   ########.fr       */
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

void	print_32(unsigned char *ptr, int i)
{
	if (!(i%4))
		ft_printf("%0.8x ", get_int_indian(get_otool(0), *(int*)(ptr + i)));
}

void	print_64(unsigned char *ptr, int i)
{
	ft_printf("%02x ", get_int_indian(get_otool(0), ptr[i]));
}

int	otool_format(t_sec section)
{
	unsigned int	i;
	t_cpu_family cpu;

	i = 0;
	t_otool *otool = get_otool(0);
	cpu = get_cpu_family(otool->head.cputype);
	while (i < section.size)
	{
		if (!(i % 16))
		{
			ft_printf(cpu.print_format, get_int_indian(otool, (long)section.addr)+ i , "        ");
		}
		cpu.print_func(section.ptr, i);
		if (++i && !(i % 16) && i < section.size)
			ft_printf("\n");
	}
	ft_putendl("");
	return (EXIT_SUCCESS);
}

void	print_otool(void *ptr, void *struc, uint32_t index)
{
	t_otool						*otool;

	(void)index;
	otool = struc;
	if (!is_text_sect(ptr, otool->head.magic))
			return ;
	set_section_values(ptr, struc); 
	ft_printf("Contents of (__TEXT,__text) section\n");
	otool_format(otool->section);
}
