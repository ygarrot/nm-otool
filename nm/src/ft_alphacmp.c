/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alphacmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 14:40:51 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/26 13:13:03 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		ft_alphacmp(void *s1, void *s2)
{
	t_nm		*nm;
	int			*index_table;
	nm = get_nm(NULL);
	if (!s1 || !s2 || !nm->head.string_table)
		return (0);

	index_table =(int[2]){ get_int_endian(nm, (*(t_list64*)s1).n_un.n_strx),
		get_int_endian(nm, ((*(t_list64*)s2).n_un.n_strx))};
	if (nm->offset_handler(nm, nm->head.string_table , index_table[0])
				|| nm->offset_handler(nm, nm->head.string_table , index_table[1]))
		return (0);
	/* ft_printf("%lld", strnlen(nm->head.string_table +  index_table[1], 1)); */
				
	/* ft_printf("%lld %lld %lld\n", index_table[1], nm->file.offset, */
			/* (long)nm->file.offset - (long)nm->head.string_table ); */
	int cmp = ft_strcmp(nm->head.string_table + index_table[0],
				nm->head.string_table + index_table[1]);
	if (cmp)
		return cmp;
	return get_int_endian(nm, (*(t_list64*)s1).n_value)- get_int_endian(nm, (*(t_list64*)s2).n_value);
}
