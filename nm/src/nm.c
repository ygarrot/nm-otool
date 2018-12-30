/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 14:15:58 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/30 15:37:07 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_output(int nsyms, int symoff, int stroff, void *ptr, t_nm *nm)
{
	int		i;
	char		*string_table;
	t_list64 *array;

	array = ptr + symoff;
	string_table = ptr + stroff;
	for (i = 0; i < nsyms; ++i)
	{
		btree_insert_data(&nm->btree, &array[i], ft_alphacmp, ft_del_nothing);
	}
			/* print_nm_format(array[i], string_table, nm); */
			iter_btree(&nm->btree, nm, print_nm_format);
}

void	handle64(void *ptr)
{
	int										ncmds;
	int										i;
	t_mach_header_64 			*header;
	t_load_command 				*lc;
	t_symtab_command			*sym;
	t_segment_command_64	*segm;
	t_nm								*nm;

	header = (struct mach_header_64 *) ptr;
	ncmds = header->ncmds;
	lc = (void*) ptr + sizeof(*header);
	nm = get_nm(NULL);
	for (i = 0; i < ncmds; ++i) 
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (t_symtab_command *)lc;	
			nm->string_table = ptr + sym->stroff;
			print_output(sym->nsyms,sym->symoff, sym->stroff, ptr, nm);
			/* iter_over_mem(ptr + sym->symoff, &nm, SYM_TAB, &print_nm_format); */ 
		}
		if (lc->cmd == LC_SEGMENT_64)
		{
			segm = (struct segment_command_64*)lc;
			iter_over_mem(segm,  &nm,SECTION_64, &set_section_addresses);
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
	/* t_nm								nm; */

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
			handle64(ptr);
		/* iter_over_mem(ptr + sizeof(t_mach_header_64), &nm, LOAD_COMMAND, &cross_command); */ 
	}
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
