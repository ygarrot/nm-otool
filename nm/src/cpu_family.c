/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_family.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 14:13:16 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/25 16:23:25 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_cpu_family	get_cpu_family(int type)
{
	static const char	*flags32 = "%08llx\t";
	static const char	*flags64 = "%016llx\t";
	int					i;
	t_cpu_family		*cpu_family;

	i = 0;
	cpu_family = (t_cpu_family[14]){
		{ CPU_TYPE_VAX, "vax", 8, 0xffff, flags32},
		{ CPU_TYPE_MC680x0, "mc680", 8, 0xffff, flags32},
		{ CPU_TYPE_X86, "i386", 8, 0xffff, flags32},
		{ CPU_TYPE_I386, "i386", 8, 0xffff, flags32},
		{ CPU_TYPE_X86_64, "x86_64", 16, 0xffffffff, flags64},
		{ CPU_TYPE_MC98000, "mc98000", 8, 0xffff, flags32},
		{ CPU_TYPE_HPPA, "hppa", 8, 0xffff, flags32},
		{ CPU_TYPE_ARM64, "arm64", 16, 0xffffffff, flags64},
		{ CPU_TYPE_ARM, "arm", 8, 0xffffff, flags32},
		{ CPU_TYPE_SPARC, "sparc", 8, 0xffff, flags32},
		{ CPU_TYPE_I860, "i860", 8, 0xffff, flags32},
		{ CPU_TYPE_POWERPC, "ppc", 8, 0xffffff, flags32},
		{ CPU_TYPE_POWERPC64, "ppc64", 8, 0xffff, flags32},
		{ -1, "?", 16, 0xffffffff, flags64}
	};
	while (cpu_family[i].type != -1 && cpu_family[i].type != type)
		i++;
	return (cpu_family[i]);
}

char			*print_arch(char *file_name, void *ptr)
{
	t_cpu_family		cpu;
	int					is_lib;

	if (!get_nm(0)->head.no_arch)
		return (0);
	cpu = get_cpu_family(get_int_endian(get_nm(0),
				*(unsigned int*)(ptr + sizeof(unsigned int))));
	is_lib = ft_memcmp(ptr, ARLIB, ft_strlen(ARLIB));
	if (!is_lib)
		ft_printf("Archive : ");
	if (file_name)
		ft_printf("\n%s", file_name);
	if (*cpu.name != '?' && get_nm(0)->head.no_arch)
		ft_printf(" (for architecture %s)", cpu.name);
	ft_printf(is_lib ? ":\n" : "\n");
	return (NULL);
}
