/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 11:34:41 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/12 15:40:33 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_macho.h"

int		get_magic(void *ptr)
{
	int		magic_number;

	magic_number = *(int *)ptr;
	return (magic_number);
}

int		get_iter_nb(void *ptr, void *struc, int type)
{
	t_segment_command_64	*segment_command64;
	t_segment_command		*segment_command;
	t_macho					*macho;

	macho = struc;
	if (type == LOAD_COMMAND)
		return (macho->mem.iter_nb);
	if (type == SECTION_64)
	{
		segment_command64 = (ptr - sizeof(t_segment_command_64));
		return (get_int_endian(macho, segment_command64->nsects));
	}
	if (type == SECTION)
	{
		segment_command = (ptr - sizeof(t_segment_command));
		return (get_int_endian(macho, segment_command->nsects));
	}
	if (type == SYM_TAB)
		return (macho->mem.iter_nb);
	if (type == SYM_TAB_L)
		return (UINT_MAX);
	return (0);
}

int		get_inc_value(void *ptr, void *struc, int type)
{
	char		**str;
	int			size;

	if (type == LOAD_COMMAND)
		return (get_int_endian(struc, ((t_load_command *)ptr)->cmdsize));
	if (type == SECTION_64)
		return (sizeof(t_section_64));
	if (type == SECTION)
		return (sizeof(t_section));
	if (type == SYM_TAB)
		return (0);
	if (type == SYM_TAB_L)
	{
		str = ft_strsplit(ptr, ' ');
		if (ft_tablen(str) < 5)
		{
			ft_free_dblechar_tab(str);
			return (INT_MAX);
		}
		size = ft_atoi(str[5]);
		ft_free_dblechar_tab(str);
		return (size + 60);
	}
	return (0);
}

void	iter_over_mem(void *child, void *struc, int type,
		void (*f)(void *elem, void *struc, uint32_t index))
{
	t_macho		*macho;
	uint32_t	iter_nb;
	uint32_t	i;
	int			inc_value;

	macho = struc;
	i = -1;
	iter_nb = get_iter_nb(child, struc, type);
	while (++i < iter_nb)
	{
		(*f)(child, struc, i);
		inc_value = get_inc_value(child, struc, type);
		if (macho->error || macho->offset_handler(macho, child, inc_value))
			return ;
		child = (void *)child + inc_value;
	}
}
