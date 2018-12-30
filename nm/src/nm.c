/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 14:15:58 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/30 17:40:28 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		ft_error(char *str)
{
	ft_putstr(str);
	return (-1);
}

void		get_arch(void *ptr)
{
	unsigned int		magic_number;
	 t_nm								*nm; 

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
			nm = get_nm(0);
		nm->header = (t_mach_header_64*)ptr ;
		 iter_over_mem(ptr + sizeof(t_mach_header_64), nm, LOAD_COMMAND, &cross_command);  
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
