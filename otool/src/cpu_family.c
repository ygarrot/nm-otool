/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_family.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 14:13:16 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/12 14:04:42 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

char			*print_arch(char *file_name, void *ptr)
{
	t_cpu_family		cpu;
	t_otool				*otool;
	int					is_lib;

	otool = get_otool(0);
	if (otool->symtab.active)
		return (0);
	cpu = get_cpu_family(otool->head.cpu_type, otool->head.cpu_subtype);
	is_lib = ft_memcmp(ptr, ARLIB, ft_strlen(ARLIB));
	if (!is_lib)
		ft_printf("Archive : ");
	if (file_name)
		ft_printf("%s", file_name);
	if (*cpu.name != '?' && (otool->head.active)
	&& ft_strcmp(cpu.name, "x86_64"))
		ft_printf(" (architecture %s)", cpu.name);
	ft_printf(is_lib ? ":\n" : "\n");
	ft_memdel((void**)&cpu.name);
	return (NULL);
}
