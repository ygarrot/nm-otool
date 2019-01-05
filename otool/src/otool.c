/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:34:12 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/05 15:00:32 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		ft_error(char *file, char *str)
{
	ft_printf("'%s': %s\n", file, str);
	return (EXIT_FAILURE);
}

void		cross_arch(void *ptr, char *file_name)
{
	unsigned int		magic_number;
	t_otool								*otool; 
	int index;
	unsigned int *arch_type = 
		(unsigned int[3]){MH_MAGIC_64, MH_MAGIC, FAT_MAGIC};
	unsigned int  *arch_type_r = 
		(unsigned int[3]){MH_CIGAM_64, MH_CIGAM, FAT_CIGAM};
	void	(*func_tab[4])(void *ptr, void *otool) = 
	{handle_header64, handle_header32,is_fat_header, ranlib_handler};

	if (!ptr)
		return ;
	otool = get_otool(0);
	magic_number = *(unsigned int *)ptr;
	otool->magic_number = magic_number;
	otool->header  = ptr;
	if ((index = ft_uint_isin(magic_number, arch_type_r, 3)) > 0
			||(index = ft_uint_isin(magic_number, arch_type , 3)) > 0
			|| (!ft_memcmp(ptr, ARLIB, ft_strlen(ARLIB)) && (index = 4)))
	{
		if (index == 4)
			ft_printf("Archive : ");
		if (file_name)
			ft_printf("%s%s", file_name, index == 4 ? "\n" : ":\n");
		func_tab[index - 1](ptr, otool);
	}
	else
		ft_printf(" %s\n", NOTOBJ);
	/* ft_printf("T ki %#x  %d?\n", magic_number, magic_number); */
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
	cross_arch(ptr, file);
	if (munmap(ptr, buf.st_size))
		return (ft_error(file, "munmap errror"));
	return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	int		i;
	int		ret;

	i = 0;
	if (ac < 2)
		return (mmap_file("./a.out"));
	while (++i < ac)
		if ((ret = mmap_file(av[i])) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
