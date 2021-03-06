/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 14:47:16 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/29 17:14:00 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	get_flag_from_section(int type, long sect_address[TEXT_ADD + 1])
{
	t_list_temp	*template;

	template = (t_list_temp[5]){
		{sect_address[DATA_ADD], 'd'},
			{sect_address[BSS_ADD], 'b'},
			{sect_address[TEXT_ADD], 't'},
			{-1, 's'}};
	return (get_flag_from_template(template, type));
}

char	get_flag(t_list64 list, int type, t_nm *nm)
{
	static t_list_temp	*template;
	t_cpu_family		cpu;
	char				flag;

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
	{
		cpu = get_cpu_family(nm);
		flag = get_flag_from_template(template, list.n_type & N_TYPE);
		if (flag == 'u' && (list.n_value & cpu.mask))
			flag = 'c';
		ft_memdel((void**)&cpu.name);
	}
	return (list.n_type & N_EXT ? ft_toupper(flag) : flag);
}

int		undefined_only(char flag, t_nm *nm, t_list64 list)
{
	if (ft_tolower(flag) == 'u')
		ft_printf("%s\n", nm->head.string_table + list.n_un.n_strx);
	return (1);
}

void	print_value(t_nm *nm, char flag, t_list64 list)
{
	t_cpu_family	cpu;

	cpu = get_cpu_family(nm);
	(nm->opt & PRINT_FILE_NAME) ? ft_printf("%s: ", nm->file.name) : 0;
	if (nm->head.magic == MH_MAGIC)
	{
		(ft_tolower(flag) != 'u') ? ft_printf("%0*llx", cpu.width,
				list.n_value & (uint32_t)cpu.mask)
			: ft_printf("%*c", cpu.width, ' ');
	}
	else
	{
		(ft_tolower(flag) != 'u') ? ft_printf("%0*llx",
				cpu.width, list.n_value & (int)cpu.mask)
			: ft_printf("%*c", cpu.width, ' ');
	}
	ft_printf(" %c %s\n", flag, nm->head.string_table + list.n_un.n_strx);
	ft_memdel((void**)&cpu.name);
}

void	print_nm_format(void *ptr)
{
	t_nm			*nm;
	t_list64		list;
	char			flag;

	list = *((t_list64 *)ptr);
	nm = get_nm(0);
	list.n_un.n_strx = get_int_endian(nm, list.n_un.n_strx);
	list.n_value = get_int_endian(nm, list.n_value);
	if (((nm->opt & EXTERN_ONLY) && !(list.n_type & N_EXT))
			|| list.n_type & N_STAB
			|| nm->offset_handler(nm, nm->head.string_table, list.n_un.n_strx))
		return ;
	if (ft_tolower(flag = get_flag(list, 0, nm)) == 'u'
			&& nm->opt & DEFINED_ONLY)
		return ;
	(nm->opt & UNDEFINED_ONLY) ? (undefined_only(flag, nm, list)) : 0;
	if (nm->opt & UNDEFINED_ONLY)
		return ;
	print_value(nm, flag, list);
}
