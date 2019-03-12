/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_family.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 14:13:16 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/12 15:40:41 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <mach-o/arch.h>

char			*print_arch(char *file_name, void *ptr)
{
	t_cpu_family		cpu;
	t_nm				*nm;
	int					is_lib;

	nm = get_nm(0);
	if (nm->symtab.active || (!nm->head.no_arch && nm->file.ac <= 1))
		return (0);
	cpu = get_cpu_family(nm);
	is_lib = ft_memcmp(ptr, ARLIB, ft_strlen(ARLIB));
	if (!is_lib)
		ft_printf("Archive : ");
	if (file_name)
		ft_printf("\n%s", file_name);
	if (*cpu.name != '?' && nm->head.no_arch && ft_strcmp(cpu.name, "x86_64"))
		ft_printf(" (for architecture %s)", cpu.name);
	ft_memdel((void**)&cpu.name);
	ft_printf(is_lib ? ":\n" : "\n");
	return (NULL);
}
