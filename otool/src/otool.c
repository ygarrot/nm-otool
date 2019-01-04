/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:34:12 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/04 17:03:37 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		ft_error(char *file, char *str)
{
	ft_printf("'%s' %s\n", file, str);
	return (-1);
}

int	swap_int(int num)
{
	int swapped = ((num>>24)&0xff) |
		((num<<8)&0xff0000) |
		((num>>8)&0xff00) |
		((num<<24)&0xff000000);
	return swapped;
}


int		get_value_from_addr(unsigned char *map, int index, int nb_bytes)
{
	int ret;
	int i;

	ret = 0;
	i = -1;
	while (++i < nb_bytes)
		ret = (ret << 8) | map[index + i];
	return (ret);
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
	magic_number = *(unsigned int *)ptr;
	otool->magic_number = magic_number;
		otool->header  = ptr;
	if (magic_number == MH_MAGIC_64)
	{	
		otool->iter_nb = ((t_mach_header_64*)ptr)->ncmds;
		iter_over_mem(ptr + sizeof(t_mach_header_64), otool, LOAD_COMMAND, &cross_command);  
	}
	else if (magic_number == MH_MAGIC)
	{
		otool->iter_nb = ((t_mach_header*)ptr)->ncmds;
		iter_over_mem(ptr + sizeof(t_mach_header), otool, LOAD_COMMAND, &cross_command);
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		is_fat_header(ptr);
	else if (!ft_memcmp(ptr, ARLIB, ft_strlen(ARLIB)))
		ranlib_handler(ptr, otool);
	else {
		/* ft_printf("T ki %#x  %d?\n", magic_number, magic_number); */
		ft_printf(NOTOBJ);
	}
}

int	mmap_file(char *file)
{
	int 		fd;
	char		*ptr;
	struct	stat buf;
	t_otool	*otool;


	if ((fd = open(file, O_RDONLY)) < 0)
		return (ft_error(file, FT_ENOENT));
	if (fstat(fd, &buf) < 0)
		return (ft_error(file, "fstat"));
	if (is_directory(fd))
		return (ft_error(file, FT_EISDIR));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (ft_error(file, "mmap errror"));
	otool = get_otool(0);
	otool->offset = ptr+buf.st_size;
	otool->file_name = file;
	ft_printf("%s:\n", file);
	cross_arch(ptr);
	if (munmap(ptr, buf.st_size))
		return (ft_error(file, "munmap errror"));
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
