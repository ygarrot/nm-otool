/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 14:15:58 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/26 17:10:04 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
void	print_output(int nsyms, int symoff, int stroff, char *ptr)
{
		int		i;
		char		*string_table;
		struct	nlist_64	*array;
		
		array = (void*)ptr + symoff;
		string_table = ptr + stroff;
		for (i = 0; i < nsyms; ++i)
		{
			ft_printf("%s\n", array[i].n_un.n_strx);
		}
}

void	handle64(void *ptr)
{
		int		ncmds;
		int		i;
		struct	mach_header_64	*header;
		struct	load_command *lc;
		struct	symtab_command	*sym;

		header = (struct mach_header_64 *) ptr;
		ncmds = header->ncmds;
		lc = (void*) ptr - sizeof(*header);
		for (i = 0; i < ncmds; i++) 
		{
			if (lc->cmd == LC_SYMTAB)
			{
				sym = (struct symtab_command *)lc;	
				break;
			}
			lc = (void*)lc + lc->cmdsize;
		}
}

int		ft_error(char *str)
{
		ft_putstr(str);
		return (-1);
}

void		get_arch(void *ptr)
{
	unsigned int		magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle64(ptr);
}

int main(int ac, char **av)
{
	int 		fd;
	char		*ptr;
	struct	stat buf;
	if (ac != 2)
		return (ft_error("please give me an arg"));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (ft_error("error open\n"));
	if (fstat(fd, &buf) < 0)
		return (ft_error("fstat"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (ft_error("mmap errror\n"));
	get_arch(ptr);
	return (EXIT_SUCCESS);
}
