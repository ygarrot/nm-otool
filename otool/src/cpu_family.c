/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_family.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 14:13:16 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/06 17:16:21 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_cpu_family get_cpu_family(int type )
{
	char * flags32 = "%08llx\t";
	char * flags64 = "%016llx\t";
	int		i;

	i = 0;
	t_cpu_family cpu_family[14] ={
		{ CPU_TYPE_VAX ,"vax", flags32, print_32},
		{ CPU_TYPE_MC680x0 ,"mc680", flags32, print_32},
		{ CPU_TYPE_X86  ,"i386", flags32, print_64},
		{ CPU_TYPE_I386 ,"i386", flags32, print_32},
		{ CPU_TYPE_X86_64 ,"x86_64", flags64, print_64},
		{ CPU_TYPE_MC98000 ,"mc98000", flags32, print_32},
		{ CPU_TYPE_HPPA ,"hppa", flags32, print_32},
		{ CPU_TYPE_ARM64 ,"arm64", flags64, print_32},
		{ CPU_TYPE_ARM ,"arm", flags32, print_32},
		{ CPU_TYPE_SPARC ,"sparc", flags32, print_32},
		{ CPU_TYPE_I860 ,"i860", flags32, print_32},
		{ CPU_TYPE_POWERPC ,"ppc", flags32, print_32},
		{ CPU_TYPE_POWERPC64 ,"ppc64", flags32, print_32},
		{ -1,"?", flags64, print_64}
	};
	while (cpu_family[i].type != -1 && cpu_family[i].type != type)
		i++;
	return (cpu_family[i]);
}

char		*print_arch(char *file_name, void *ptr)
{
	t_cpu_family		cpu;

	get_cpu_family(
		int is_lib = ft_memcmp(ptr, ARLIB, ft_strlen(ARLIB));
			ft_printf("Archive : ");
		if (file_name)
			ft_printf("%s%s", file_name, is_lib ? "\n" : ":\n");


}
