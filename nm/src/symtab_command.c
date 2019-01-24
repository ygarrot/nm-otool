/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 17:23:51 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/24 17:55:36 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"


void	apply_sort_sym(void *ptr, void *struc, uint32_t index)
{
	t_nm *nm;

	(void)index;
	nm = struc;
	if (nm->head.magic == MH_MAGIC_64)
		btree_insert_data(&nm->btree, &(((t_list64*)ptr)[index]), ft_alphacmp, ft_del_nothing);
	else
		btree_insert_data(&nm->btree, &(((t_nlist*)ptr)[index]), ft_alphacmp, ft_del_nothing);
}

void	apply_symtab(t_symtab_command *sym, t_nm *nm)
{
	nm->head.string_table = nm->head.ptr +  sym->stroff;
	nm->mem.iter_nb = sym->nsyms;
	ft_printf("iter_nb:%d", nm->mem.iter_nb);
	iter_over_mem(nm->head.ptr + sym->symoff, nm, SYM_TAB, &apply_sort_sym);
	iter_btree(&nm->btree, nm, print_nm_format);
}
