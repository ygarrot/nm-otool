/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alphacmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 14:40:51 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/29 11:43:39 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		digit_cmp(void *s1, void *s2)
{
	long			tab[2];
	t_cpu_family	cpu;
	t_nm			*nm;

	nm = get_nm(0);
	cpu = get_cpu_family(nm);
	tab[0] = get_int_endian(nm, (*(t_list64*)s1).n_value);
	tab[1] = get_int_endian(nm, (*(t_list64*)s2).n_value);
	ft_memdel((void**)&cpu.name);
	if (!(tab[0] - tab[1]))
		return (0);
	return (tab[0] < tab[1] ? -1 : 1);
}

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
	if (nm->offset_handler(nm, nm->head.string_table, index_table[0])
			|| nm->offset_handler(nm, nm->head.string_table, index_table[1]))
		return (0);
	cmp = ft_strcmp(nm->head.string_table + index_table[0],
			nm->head.string_table + index_table[1]);
	cmp = cmp ? cmp : digit_cmp(s1, s2);
	return (nm->opt & REVERSE_SORT ? -cmp : cmp);
}

int		ft_digitcmp(void *s1, void *s2)
{
	t_nm			*nm;
	int				cmp;

	nm = get_nm(0);
	if (!s1 || !s2)
		return (0);
	cmp = digit_cmp(s1, s2);
	if (nm->opt & REVERSE_SORT)
		cmp = cmp ? cmp : -ft_alphacmp(s1, s2);
	else
		cmp = cmp ? cmp : ft_alphacmp(s1, s2);
	return (nm->opt & REVERSE_SORT ? -cmp : cmp);
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
