/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alphacmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 14:40:51 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/30 14:46:53 by ygarrot          ###   ########.fr       */
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

void	ft_del_nothing(void *why)
{
	return ; 
}

int		ft_alphacmp(void *s1, void *s2)
{
	t_nm		*nm;

	if (!s1 || !s2)
		return (0);
	nm = get_nm(NULL);
	return (ft_strcmp(nm->string_table + ((t_list64*)s1)->n_un.n_strx,
				nm->string_table + (((t_list64*)s2)->n_un.n_strx)));
}
