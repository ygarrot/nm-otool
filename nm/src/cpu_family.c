/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_family.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 14:13:16 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/28 14:37:58 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <mach-o/arch.h>

char			delspace(char *ptr)
{
	if (*ptr == ' ')
		*ptr = *(ptr + 1);
	return (*ptr);
}

t_cpu_family	insert_name(t_nm *nm, t_cpu_family *cpu)
{
	NXArchInfo	*archInfo;

	archInfo = (NXArchInfo*)NXGetArchInfoFromCpuType(nm->head.cpu_type,
			nm->head.cpu_subtype);
	cpu->name = archInfo ? ft_strmap2(ft_strdup(archInfo->name),
			delspace) : strdup(cpu->name);
	return (*cpu);
}

t_cpu_family	get_cpu_family(t_nm *nm)
{
	static const char	*flags32 = "%08llx\t";
	static const char	*flags64 = "%016llx\t";
	int					i;
	t_cpu_family		*cpu_family;

	i = 0;
	cpu_family = (t_cpu_family[14]){
		{ CPU_TYPE_VAX, "vax", 8, 0xffffff, flags32},
			{ CPU_TYPE_MC680x0, "mc680", 8, 0xffff, flags32},
			{ CPU_TYPE_X86, "i386", 8, 0xffffff, flags32},
			{ CPU_TYPE_I386, "i386", 8, 0xffffff, flags32},
			{ CPU_TYPE_X86_64, "x86_64", 16, 0xffffffff, flags64},
			{ CPU_TYPE_MC98000, "mc98000", 8, 0xffff, flags32},
			{ CPU_TYPE_HPPA, "hppa", 8, 0xffffff, flags32},
			{ CPU_TYPE_ARM64, "arm64", 16, 0xffffffff, flags64},
			{ CPU_TYPE_ARM, "arm", 8, 0xffffff, flags32},
			{ CPU_TYPE_SPARC, "sparc", 8, 0xffffff, flags32},
			{ CPU_TYPE_I860, "i860", 8, 0xffffff, flags32},
			{ CPU_TYPE_POWERPC, "ppc", 8, 0xffffff, flags32},
			{ CPU_TYPE_POWERPC64, "ppc64", 8, 0xffffff, flags32},
			{ -1, "?", 16, 0xffffffff, flags64}
	};
	while (cpu_family[i].type != -1 && cpu_family[i].type != nm->head.cpu_type)
		i++;
	return (insert_name(nm, &cpu_family[i]));
}

char			*print_arch(char *file_name, void *ptr)
{
	t_cpu_family		cpu;
	t_nm				*nm;
	int					is_lib;

	nm = get_nm(0);
	if (!nm->head.no_arch && nm->file.ac <= 1)
		return (0);
	cpu = get_cpu_family(nm);
	is_lib = ft_memcmp(ptr, ARLIB, ft_strlen(ARLIB));
	if (!is_lib)
		ft_printf("Archive : ");
	if (file_name)
		ft_printf("\n%s", file_name);
	if (*cpu.name != '?' && (nm->head.no_arch || ft_strcmp(cpu.name, "x86_64")))
		ft_printf(" (for architecture %s)", cpu.name);
	ft_memdel((void**)&cpu.name);
	ft_printf(is_lib ? ":\n" : "\n");
	return (NULL);
}
