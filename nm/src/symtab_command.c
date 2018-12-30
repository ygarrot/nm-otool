/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 17:23:51 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/29 17:28:54 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	iter_over_symtab(t_load_command *lc)
{
	int		i;
	char		*string_table;
	t_list64 *;

	symboles = ptr + symoff;
	string_table = ptr + stroff;
	for (i = 0; i < lc->nsyms; ++i)
	{
			print_nm_format(array[i], string_table, nm);
	}
}

