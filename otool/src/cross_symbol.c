/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 17:39:02 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/12 14:21:00 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	ranlib_handler(void *ptr, t_macho *macho)
{
	t_otool			*otool;
	char			**tab;
	unsigned char	*strr;
	t_symbol_table	*table;
	int				size;

	otool = struc;
	tab = ft_strsplit((char *)ptr + 8, ' ');
	strr = (unsigned char *)ptr + 8 + ft_strlen((char *)ptr + 4);
	table = (void *)strr;
	macho->mem.iter_nb = table->size / sizeof(t_symbol_info);
	macho->symtab.symhead = ptr;
	macho->head.type = RANLIB_64;
	size = ft_atoi(tab[5]);
	ft_free_dblechar_tab(tab);
	otool->symtab.active = true;
	iter_over_mem(ptr + 68 + size, otool, SYM_TAB_L, &cross_symbol);
	otool->symtab.active = false;
}
