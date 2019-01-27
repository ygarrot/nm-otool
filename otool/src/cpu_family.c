/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_family.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 14:13:16 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/26 20:05:50 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"


char delspace(char *ptr)
{
	if (*ptr == ' ')
		*ptr = *(ptr + 1);
	return *ptr;
}

t_cpu_family insert_name(cpu_type_t type, cpu_subtype_t subtype, t_cpu_family *cpu)
{
	NXArchInfo *archInfo;

	archInfo = (NXArchInfo*)NXGetArchInfoFromCpuType(type, subtype);
	cpu->name = archInfo ? ft_strmap2(ft_strdup(archInfo->name),
			delspace) : strdup(cpu->name); 
	return (*cpu);
}

t_cpu_family	get_cpu_family(cpu_type_t type, cpu_subtype_t subtype)
{
	static const char	*flags32 = "%08llx\t";
	static const char	*flags64 = "%016llx\t";
	int					i;
	t_cpu_family		*cpu_family;

	i = 0;
	cpu_family = (t_cpu_family[14]){
		{ CPU_TYPE_VAX, "vax", flags32, print_32},
		{ CPU_TYPE_MC680x0, "mc680", flags32, print_32},
		{ CPU_TYPE_X86, "i386", flags32, print_64},
		{ CPU_TYPE_I386, "i386", flags32, print_32},
		{ CPU_TYPE_X86_64, "x86_64", flags64, print_64},
		{ CPU_TYPE_MC98000, "mc98000", flags32, print_32},
		{ CPU_TYPE_HPPA, "hppa", flags32, print_32},
		{ CPU_TYPE_ARM64, "arm64", flags64, print_32},
		{ CPU_TYPE_ARM, "arm", flags32, print_32},
		{ CPU_TYPE_SPARC, "sparc", flags32, print_32},
		{ CPU_TYPE_I860, "i860", flags32, print_32},
		{ CPU_TYPE_POWERPC, "ppc", flags32, print_32},
		{ CPU_TYPE_POWERPC64, "ppc64", flags32, print_32},
		{ -1, "?", flags32, print_32}
	};
	while (cpu_family[i].type != -1 && cpu_family[i].type != type)
		i++;
	return (insert_name(type, subtype, &cpu_family[i]));
}

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
	if (*cpu.name != '?' && (otool->head.active) && ft_strcmp(cpu.name, "x86_64"))
		ft_printf(" (architecture %s)", cpu.name);
	ft_printf(is_lib ? ":\n" : "\n");
	return (NULL);
}
