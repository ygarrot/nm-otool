/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alphacmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 14:40:51 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/30 15:35:35 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_nm	*get_nm(t_nm *ptr)
{
	static t_nm nm;

	if (ptr)
		nm = *ptr;
	return (&nm);
}

int		ft_alphacmp(void *s1, void *s2)
{
	t_nm		*nm;

	nm = get_nm(NULL);
	if (!nm->string_table)
		ft_printf("no string_table\n");
	if (!s1 || !s2 || !nm->string_table)
		return (0);
	t_list64 *elem;
	elem = (t_list64*)s1;
	ft_printf("%s %d\n", nm->string_table, (*elem).n_un.n_strx);
	ft_printf(nm->string_table + (*elem).n_un.n_strx);
	return (ft_strcmp(nm->string_table + (*(t_list64*)s1).n_un.n_strx,
				nm->string_table + ((*(t_list64*)s2).n_un.n_strx)));
}
