/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:47:16 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/29 14:57:07 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char		get_flag_from_template(t_list_temp	*template, int to_find)
{
	int	i;

	i = 0;
	while (template[i].c && template[i].symb != to_find)
		i++;
	return (template[i].c);
}

char	get_flag_from_section(int type, long sect_address[DATA_ADD + 1])
{
	t_list_temp	*template;

	template = (t_list_temp [5]){
		{sect_address[DATA_ADD], 'u'},	
			{sect_address[BSS_ADD], 'a'},	
			{sect_address[TEXT_ADD], 't'},
			{0, 0}
	};
	return get_flag_from_template(template, type);
}

char	get_flag(t_list64 ptr, int type, t_nm *nm)
{
	static	t_list_temp		*template;
	char									flag;

	(void)type;
	flag = 0;
	template = (t_list_temp [5]){
		{N_UNDF, 'u'},	
			{N_ABS, 'a'},	
			{N_SECT, 'u'},
			{N_INDR, 'i'},
			{0, 0}
	};
	if (ptr.n_type == N_SECT)
		flag = get_flag_from_section(ptr.n_type, nm->sect_address);
	else
		flag = get_flag_from_template(template, ptr.n_type);
	/* ft_printf(" n_type: %#x, n_sect: %#x, n_desc: %#x, n_value: %#x, str: ", ptr.n_type, ptr.n_sect, */
	/* 		GET_COMM_ALIGN(ptr.n_desc), ptr.n_value); */
	if (flag)
	{
		return (ptr.n_type & N_EXT ? 
				ft_toupper(flag) : flag);
	}
	return ('?');
}
