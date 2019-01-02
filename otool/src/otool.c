/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:34:12 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/02 13:41:41 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		ft_error(char *str)
{
	ft_putstr(str);
	return (-1);
}

int	swap_int(int num)
{
	int swapped = ((num>>24)&0xff) | // move byte 3 to byte 0
		((num<<8)&0xff0000) | // move byte 1 to byte 2
		((num>>8)&0xff00) | // move byte 2 to byte 1
		((num<<24)&0xff000000); // byte 0 to byte 3
	return swapped;
}

void	is_fat_header(t_fat_header *fat_header)
{
	int		offset;
	int		nfat;
	t_fat_arch *arch;

	arch = (t_fat_arch*)(fat_header + 1);
	nfat = swap_int(fat_header->nfat_arch);
	while (--nfat >= 0)
	{
		offset = swap_int(arch->offset);
		cross_arch((void*)fat_header + offset);
		arch++;
	}
}

void		cross_arch(void *ptr)
{
	unsigned int		magic_number;
	t_otool								*otool; 

	if (!ptr)
		return ;
	otool = get_otool(0);
	magic_number = *(int *)ptr;
	otool->magic_number = magic_number;
	if (magic_number == MH_MAGIC_64)
	{	
		otool->header  = ptr;
		otool->iter_nb = ((t_mach_header_64*)ptr)->ncmds;
		iter_over_mem(ptr + sizeof(t_mach_header_64), otool, LOAD_COMMAND, &cross_command);  
	}
	else if (magic_number == MH_MAGIC)
	{
		otool->header  = ptr;
		otool->iter_nb = ((t_mach_header*)ptr)->ncmds;
		iter_over_mem(ptr + sizeof(t_mach_header), otool, LOAD_COMMAND, &cross_command);
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		is_fat_header(ptr);
	else {
		ft_printf("T ki %#x?\n", magic_number);
	}
}

int	mmap_file(char *file)
{
	int 		fd;
	char		*ptr;
	struct	stat buf;

	ft_printf("%s\n", file);
	if ((fd = open(file, O_RDONLY)) < 0)
		return (ft_error("error open\n"));
	if (fstat(fd, &buf) < 0)
		return (ft_error("fstat"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (ft_error("mmap errror\n"));
	cross_arch(ptr);
	return (0);
}

int main(int ac, char **av)
{
	int		i;

	i = 0;
	if (ac < 2)
		return (mmap_file("./a.out"));
	while (++i < ac)
		mmap_file(av[i]);
	return (EXIT_SUCCESS);
}
