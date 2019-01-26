/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 17:23:51 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/26 13:12:40 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	apply_sort_sym(void *ptr, void *struc, uint32_t index)
{
	t_nm		*nm;
	t_list64	*list64;
	t_nlist		*list;

	(void)index;
	nm = struc;
	list64 = &((t_list64*)ptr)[index];
	list = &((t_nlist*)ptr)[index];
	if (get_int_endian(nm, nm->head.magic) == MH_MAGIC_64)
		btree_insert_data(&nm->btree, list64, ft_alphacmp, ft_del_nothing);
	else
		btree_insert_data(&nm->btree, list, ft_alphacmp, ft_del_nothing);
}

void	apply_symtab(t_symtab_command *sym, t_nm *nm)
{
	if (nm->offset_handler(nm, nm->head.ptr, get_int_endian(nm, sym->stroff)))
		return ;
	nm->head.string_table = nm->head.ptr + get_int_endian(nm, sym->stroff);
	nm->mem.iter_nb = get_int_endian(nm, sym->nsyms);
	iter_over_mem(nm->head.ptr + get_int_endian(nm, sym->symoff),
	nm, SYM_TAB, &apply_sort_sym);
	if (nm->error)
		return ;
	iter_btree(&nm->btree, nm, print_nm_format);
}
