/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 17:23:51 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/30 17:40:02 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"


void	apply_sort_sym(void *ptr, void *struc, uint32_t index)
{
	t_nm *nm;

	(void)index;
	nm = struc;
	btree_insert_data(&nm->btree, &(((t_list64*)ptr)[index]), ft_alphacmp, ft_del_nothing);
}
void	apply_symtab(t_symtab_command *sym, t_nm *nm)
{
	nm->string_table = nm->header +  sym->stroff;
	nm->iter_nb = sym->nsyms;
	iter_over_mem(nm->header + sym->symoff, nm, SYM_TAB, &apply_sort_sym);
	iter_btree(&nm->btree, nm, print_nm_format);
}
