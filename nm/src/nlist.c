/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:47:16 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/26 12:53:11 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char get_flag_from_template(t_list_temp *template, int to_find)
{
	int i;

	i = 0;
	while (template[i].symb != -1 && template[i].symb != to_find)
		i++;
	return (template[i].c);
}

char get_flag_from_section(int type, long sect_address[TEXT_ADD + 1])
{
	t_list_temp *template;

	/* ft_printf("%d %d %d type %d ", sect_address[DATA_ADD], */ 
			/* sect_address[BSS_ADD], sect_address[TEXT_ADD], type); */
	template = (t_list_temp[5]){
		{sect_address[DATA_ADD], 'd'},
		{sect_address[BSS_ADD], 'b'},
		{sect_address[TEXT_ADD], 't'},
		{-1, 's'}};
	return get_flag_from_template(template, type);
}

char get_flag(t_list64 list, int type, t_nm *nm)
{
	static t_list_temp *template;
	char flag;

	(void)type;
	flag = 0;
	template = (t_list_temp[5]){
		{N_UNDF, 'u'},
		{N_ABS, 'a'},
		{N_INDR, 'i'},
		{-1, '?'}};

	if ((list.n_type & N_TYPE) == N_SECT)
		flag = get_flag_from_section(list.n_sect, nm->sect_address);
	else
		flag = get_flag_from_template(template, list.n_type & N_TYPE);
	/* ft_printf(" n_type: %#x, n_sect: %#x, n_desc: %#x, n_value: %#x, str: ", list.n_type, list.n_sect, */
	/* 		GET_COMM_ALIGN(list.n_desc), list.n_value); */
	return (list.n_type & N_EXT ? ft_toupper(flag) : flag);
}

void print_nm_format(void *ptr, void *struc)
{
	char flag;
	t_nm *nm;
	t_cpu_family	cpu;
	t_list64 list;

	list = *((t_list64 *)ptr);
	nm = struc;
	cpu = get_cpu_family(nm->head.cputype);
	list.n_un.n_strx = get_int_endian(nm, list.n_un.n_strx);
		list.n_value = get_int_endian(nm, list.n_value);
	/* list.n_type = get_int_endian(nm, list.n_type); */
	if (list.n_type & N_STAB)
		return;
	if (!(nm->head.string_table + list.n_un.n_strx))
		return;
	if ((flag = get_flag(list, 0, nm)) != 'U')
		;
	if (tolower(flag) != 'u')
	{	
		ft_printf("%0*llx", cpu.width, list.n_value & cpu.mask);
	}
	else
		ft_printf("%*c", cpu.width, ' ');
	ft_printf(" %c %s\n", flag, nm->head.string_table + list.n_un.n_strx);
}
