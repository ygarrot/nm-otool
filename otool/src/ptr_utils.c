/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 11:34:41 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/01 17:29:56 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		get_magic(void *ptr)
{
	int magic_number;

	magic_number = *(int*)ptr;
	return magic_number;
}

t_otool		*get_otool(t_otool *ptr)
{
		static t_otool otool;

		if (ptr)
			otool = *ptr;
		return (&otool);
}

int		get_iter_nb(void *ptr, int type)
{
	t_otool *otool;

	otool = get_otool(0);
	if (type == LOAD_COMMAND)
			return (otool->iter_nb);
	if (type == SECTION_64)
			return (((t_segment_command_64*)(ptr - sizeof(t_segment_command_64)))->nsects);
	if (type == SECTION)
			return (((t_segment_command*)(ptr - sizeof(t_segment_command)))->nsects);
	return (0);
}

int		get_inc_value(void *ptr, int type)
{
	if (type == LOAD_COMMAND)
		return (((t_load_command*)ptr)->cmdsize);
	if (type == SECTION_64)
		return (sizeof(t_section_64));
	if (type == SECTION)
		return (sizeof(t_section));
	return (0);
}

void	iter_over_mem(void *child, void *struc, int type,
		void	(*f)(void *elem, void *struc, uint32_t index))
{
	uint32_t							iter_nb;
	uint32_t								i;

	i = -1;
	iter_nb = get_iter_nb(child, type);
	while (++i < iter_nb)
	{
		(*f)(child, struc, i);
		child = (void*)child + get_inc_value(child, type);
	}
}