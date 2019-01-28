/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 17:23:51 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/28 12:49:45 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	apply_sort_sym(void *ptr, void *struc, uint32_t index)
{
	t_nm		*nm;
	t_list64	*list64;
	t_nlist		*list;
	int			(*f)(void *s1, void *s2);

	(void)index;
	nm = struc;
	list64 = &((t_list64 *)ptr)[index];
	list = &((t_nlist *)ptr)[index];
	f = ft_alphacmp;
	if (nm->opt & NO_SORT || nm->opt & NUMERIC_SORT)
		f = nm->opt & NO_SORT ? ft_nosort : ft_digitcmp;
	if (get_int_endian(nm, nm->head.magic) == MH_MAGIC_64)
		btree_insert_data(&nm->btree, list64, f, ft_del_nothing);
	else
		btree_insert_data(&nm->btree, list, f, ft_del_nothing);
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
	btree_apply_infix(nm->btree, print_nm_format);
}
