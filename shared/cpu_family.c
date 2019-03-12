/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_family.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:41:36 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/12 14:05:08 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_macho.h"

char			delspace(char *ptr)
{
	if (*ptr == ' ')
		*ptr = *(ptr + 1);
	return (*ptr);
}

t_cpu_family	insert_name(t_head_utils *head, t_cpu_family *cpu)
{
	t_nxarchinfo	*arch_info;

	arch_info = (t_nxarchinfo*)NXGetArchInfoFromCpuType(head->cpu_type,
			head->cpu_subtype);
	cpu->name = arch_info ? ft_strmap2(ft_strdup(arch_info->name),
			delspace) : ft_strdup(cpu->name);
	return (*cpu);
}

t_cpu_family	get_cpu_family(t_head_utils *head)
{
	int					i;
	t_cpu_family		*cpu_family;

	i = 0;
	cpu_family = (t_cpu_family[14]){
		{ CPU_TYPE_VAX, "vax", WIDTH32, MASK64, print_32},
			{ CPU_TYPE_MC680x0, "mc680", WIDTH32, MASK32, print_64},
			{ CPU_TYPE_X86, "x86", WIDTH32, MASK64_X, print_64},
			{ CPU_TYPE_I386, "i386", WIDTH32, MASK64, print_32},
			{ CPU_TYPE_X86_64, "x86_64", WIDTH64, MASK64_X, print_64},
			{ CPU_TYPE_MC98000, "mc98000", WIDTH32, MASK32, print_32},
			{ CPU_TYPE_HPPA, "hppa", WIDTH32, MASK64, print_32},
			{ CPU_TYPE_ARM64, "arm64", WIDTH64, MASK64_X, print_32},
			{ CPU_TYPE_ARM, "arm", WIDTH32, MASK64, print_32},
			{ CPU_TYPE_SPARC, "sparc", WIDTH32, MASK64, print_32},
			{ CPU_TYPE_I860, "i860", WIDTH32, MASK64, print_32},
			{ CPU_TYPE_POWERPC, "ppc", WIDTH32, MASK64, print_32},
			{ CPU_TYPE_POWERPC64, "ppc64", WIDTH32, MASK64, print_32},
			{ -1, "?", WIDTH64, MASK64_X, print_32}
	};
	while (cpu_family[i].type != -1 && cpu_family[i].type != head->cpu_type)
		i++;
	return (insert_name(head, &cpu_family[i]));
}


