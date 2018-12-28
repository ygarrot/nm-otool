/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:47:16 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/28 17:11:18 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	get_flag(t_list64 ptr, int type)
{
	static t_list_temp		*template;
	int						i;

	(void)type;
	i = 0;
	template = (t_list_temp [5]){
		{N_UNDF, 'u'},	
			{N_ABS, 'a'},	
			{N_SECT, 'u'},
			{N_INDR, 'i'},
	};
	ft_printf(" n_type: %#x, n_sect: %#x, n_desc: %#x, n_value: %#x, str: ", ptr.n_type, ptr.n_sect,
			GET_COMM_ALIGN(ptr.n_desc), ptr.n_value);
	while (i < 4  && ptr.n_type != template[i].symb)
		++i;
	if (i < 4)
	{
		ft_printf(" GOT: %c ", template[i].c);
		return (ptr.n_type & N_EXT ? 
				ft_toupper(template[i].c) : template[i].c);
	}
	return ('?');
}
