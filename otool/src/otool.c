/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:34:12 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/26 18:41:14 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		ft_error(char *file, char *str)
{
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (EXIT_FAILURE);
}

int		is_valid_arch(unsigned int magic_number, t_otool *otool, void *ptr)
{
	int				index;
	unsigned int	*arch_type;
	unsigned int	*arch_type_r;
	void			(*const func_tab[4])(void *ptr,
			void *otool) = {handle_header64,
		handle_header32, is_fat_header, ranlib_handler};

	arch_type = (unsigned int[3]){MH_MAGIC_64, MH_MAGIC, FAT_MAGIC};
	arch_type_r = (unsigned int[3]){MH_CIGAM_64, MH_CIGAM, FAT_CIGAM};
	if (((index = ft_uint_isin(magic_number, arch_type_r, 3)) > 0
				&& (otool->mem.is_big_endian = true))
			|| (index = ft_uint_isin(magic_number, arch_type, 3)) > 0
			|| (!ft_memcmp(ptr, ARLIB, ft_strlen(ARLIB)) && (index = 4)))
	{
		index != 3 ? print_arch(otool->file.name, ptr) : 0;
		func_tab[index - 1](ptr, otool);
	}
	return (-1);
}

int		cross_arch(void *ptr, char *file_name)
{
	unsigned int	magic_number;
	t_otool			*otool;

	if (!ptr)
		return (EXIT_FAILURE);
	otool = get_otool(0);
	magic_number = *(unsigned int *)ptr;
	otool->head.magic = magic_number;
	otool->head.ptr = ptr;
	if (!is_valid_arch(magic_number, otool, ptr))
		ft_error(file_name, NOTOBJ);
	return (otool->error);
}

int		mmap_file(char *file)
{
	int			ret;
	int			fd;
	char		*ptr;
	struct stat	buf;
	t_otool		*otool;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (ft_error(file, FT_ENOENT));
	if (fstat(fd, &buf) < 0)
		return (ft_error(file, "fstat"));
	if (is_directory(fd))
		return (ft_error(file, FT_EISDIR));
	if ((ptr = mmap(0, buf.st_size,
			PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (ft_error(file, "mmap errror"));
	otool = get_otool(0);
	otool->file.offset = ptr + buf.st_size;
	otool->head.no_arch = 0;
	otool->file.name = file;
	ret = cross_arch(ptr, file);
	if (munmap(ptr, buf.st_size))
		return (ft_error(file, "munmap errror"));
	return (ret == 1);
}

int		main(int ac, char **av)
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
