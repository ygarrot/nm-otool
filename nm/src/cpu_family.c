/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_family.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 14:13:16 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/24 17:56:44 by ygarrot          ###   ########.fr       */
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
		{ CPU_TYPE_VAX, "vax", flags32},
		{ CPU_TYPE_MC680x0, "mc680", flags32},
		{ CPU_TYPE_X86, "i386", flags32},
		{ CPU_TYPE_I386, "i386", flags32},
		{ CPU_TYPE_X86_64, "x86_64", flags64},
		{ CPU_TYPE_MC98000, "mc98000", flags32},
		{ CPU_TYPE_HPPA, "hppa", flags32},
		{ CPU_TYPE_ARM64, "arm64", flags64},
		{ CPU_TYPE_ARM, "arm", flags32},
		{ CPU_TYPE_SPARC, "sparc", flags32},
		{ CPU_TYPE_I860, "i860", flags32},
		{ CPU_TYPE_POWERPC, "ppc", flags32},
		{ CPU_TYPE_POWERPC64, "ppc64", flags32},
		{ -1, "?", flags64}
	};
	while (cpu_family[i].type != -1 && cpu_family[i].type != type)
		i++;
	return (cpu_family[i]);
}

char			*print_arch(char *file_name, void *ptr)
{
	t_cpu_family		cpu;
	int					is_lib;

	cpu = get_cpu_family(get_int_indian(get_nm(0),
				*(unsigned int*)(ptr + sizeof(unsigned int))));
	is_lib = ft_memcmp(ptr, ARLIB, ft_strlen(ARLIB));
	if (!is_lib)
		ft_printf("Archive : ");
	if (file_name)
		ft_printf("%s", file_name);
	if (*cpu.name != '?' && get_nm(0)->head.no_arch)
		ft_printf(" (architecture %s)", cpu.name);
	ft_printf(is_lib ? ":\n" : "\n");
	return (NULL);
}