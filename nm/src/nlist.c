/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:47:16 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/31 16:40:21 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char		get_flag_from_template(t_list_temp	*template, int to_find)
{
	int	i;

	i = 0;
	while (template[i].symb != -1 && template[i].symb != to_find)
		i++;
	return (template[i].c);
}

char	get_flag_from_section(int type, long sect_address[TEXT_ADD + 1])
{
	t_list_temp	*template;

	template = (t_list_temp [5]){
		{sect_address[DATA_ADD], 'd'},	
			{sect_address[BSS_ADD], 'b'},	
			{sect_address[TEXT_ADD], 't'},
			{-1, 's'}
	};
	return get_flag_from_template(template, type);
}

char	get_flag(t_list64 list, int type, t_nm *nm)
{
	static	t_list_temp		*template;
	char									flag;

	(void)type;
	flag = 0;
	template = (t_list_temp [5]){
		{N_UNDF, 'u'},	
			{N_ABS, 'a'},	
			{N_INDR, 'i'},
			{-1, '?'}
	};

	if ((list.n_type & N_TYPE) == N_SECT)
		flag = get_flag_from_section(list.n_sect, nm->sect_address);
	else
		flag = get_flag_from_template(template, list.n_type & N_TYPE);
	/* ft_printf(" n_type: %#x, n_sect: %#x, n_desc: %#x, n_value: %#x, str: ", list.n_type, list.n_sect, */
	/* 		GET_COMM_ALIGN(list.n_desc), list.n_value); */
	return (list.n_type & N_EXT ? ft_toupper(flag) : flag);
}

void		print_nm_format(void *ptr, void *struc)
{
	char	flag;
	t_nm	*nm;
	char	*string_table;
	int		mask;
	t_list64 list;

	list = *((t_list64*)ptr);
	nm = struc;
	mask = (nm->current_arch == MH_MAGIC_64 ? 0xffffff : 0xff);
	string_table = nm->string_table;
	if (list.n_type & N_STAB)
		return ;
	if (!*(string_table + list.n_un.n_strx))
		return ;
	if ((flag = get_flag(list, 0, nm)) != 'U')
		;
	int format = (mask == 0xff ? 8 : 16);
		if (list.n_value & mask)
			ft_printf("%0*llx", format,list.n_value );
		else
			ft_printf("%*c",format, ' ');
		ft_printf(" %c %s\n", flag, string_table + list.n_un.n_strx);
	}
