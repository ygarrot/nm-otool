/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 11:34:41 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/31 14:42:47 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/* void	*get_ptr_from_value(void *ptr, int value) */
/* { */
/* 	t_ptr **ptr_template; */

/* 	template = (t_ptr[5]*){ */
/* 		(t_segment_command_64 *)ptr, */
/* 		(t_load_command*)ptr, */
/* 		(t_mach_header_64)ptr, */
/* 		(t_symtab_command*)ptr, */
/* 	} */
/* 	return (template[value]); */
/* } */


int		get_magic(void *ptr)
{
	int magic_number;

	magic_number = *(int*)ptr;
	return magic_number;
}

int		get_iter_nb(void *ptr, int type)
{
	t_nm *nm;

	if (!(nm = get_nm(0)))
		return (0);
	if (type == LOAD_COMMAND)
			return (nm->iter_nb);
	if (type == MACH_HEADER)
		return (nm->iter_nb);
	if (type == SYM_TAB)
			return (nm->iter_nb);
	if (type == SECTION_64)
			return (((t_segment_command_64*)(ptr - sizeof(t_segment_command_64)))->nsects);
	if (type == SECTION)
			return (((t_segment_command*)(ptr - sizeof(t_segment_command)))->nsects);
	return (0);
}

int		get_inc_value(void *ptr, int type)
{
	/* if (type == MACH_HEADER) */
	/* 	return ((t_fat_arch*)ptr->offset); */ 
	if (type == LOAD_COMMAND)
		return (((t_load_command*)ptr)->cmdsize);
	if (type == SYM_TAB)
		return (0);
	if (type == SECTION_64)
		return (sizeof(t_section_64));
	if (type == SECTION)
		return (sizeof(t_section));
	return (0);
}

void	iter_over_mem(void *ptr, void *struc, int type,
		void	(*f)(void *elem, void *struc, uint32_t index))
{
	void						*child;
	uint32_t							iter_nb;
	uint32_t								i;

	i = -1;
	iter_nb = get_iter_nb(ptr, type);
	child = ptr;
	while (++i < iter_nb)
	{
		(*f)(child, struc, i);
		child = (void*)child + get_inc_value(child, type);
	}
}
