/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alphacmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 14:40:51 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/27 19:03:24 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		ft_alphacmp(void *s1, void *s2)
{
	t_nm		*nm;
	int			cmp;
	int			*index_table;

	nm = get_nm(NULL);
	if (!s1 || !s2 || !nm->head.string_table)
		return (0);
	index_table = (int[2]){ get_int_endian(nm, (*(t_list64*)s1).n_un.n_strx),
		get_int_endian(nm, ((*(t_list64*)s2).n_un.n_strx))};
	/* ft_printf("%d %d\n", index_table[0], index_table[1]); */
	if (nm->offset_handler(nm, nm->head.string_table, index_table[0])
			|| nm->offset_handler(nm, nm->head.string_table, index_table[1]))
		return (0);
	cmp = ft_strcmp(nm->head.string_table + index_table[0],
			nm->head.string_table + index_table[1]);
	cmp = cmp ? cmp : get_int_endian(nm, (*(t_list64*)s1).n_value)
			- get_int_endian(nm, (*(t_list64*)s2).n_value);
	return nm->opt & REVERSE_SORT ? -cmp : cmp;
}

int		ft_digitcmp(void *s1, void *s2)
{
	t_nm		*nm;
	t_cpu_family	cpu;
	int			cmp;

	nm = get_nm(0);
	if (!s1 || !s2)
		return (0);
	/* if(get_int_endian(nm, (*(t_list64*)s1).n_value)) */
		/* return 1; */
	cpu = get_cpu_family(nm);
	/* ft_printf("%016llx", (*(t_list64*)s1).n_value ); */
	/* ft_printf("  %016llx\n", (*(t_list64*)s2).n_value  ); */
	cmp = get_int_endian(nm, (*(t_list64*)s1).n_value)
			- get_int_endian(nm, (*(t_list64*)s2).n_value) ;
	cmp = cmp ? cmp : ft_alphacmp(s1, s2);
	return nm->opt & REVERSE_SORT ? -cmp : cmp;
}

int		ft_nosort(void *s1, void *s2)
{
	(void)s1;
	(void)s2;
	return (0);
}

int		ft_sizesort(void *s1, void *s2)
{
	(void)s1;
	(void)s2;
	return (1);
}
