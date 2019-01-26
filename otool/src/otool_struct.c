/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:42:36 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/26 18:41:14 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		offset_handler(t_otool *otool, void *ptr, int inc_value)
{
if (otool->error == 2)
	{
		otool->error = 0;
		return (1);
	}
	otool->error = (otool->file.offset < ptr + inc_value
			|| (otool->file.offset - ptr + inc_value < 0));
	if (otool->error)
		ft_error(otool->file.name, "truncated or malformed object");
	return (otool->error);
}

t_otool	*get_otool(t_otool *ptr)
{
	static t_otool otool;

	if (ptr)
		otool = *ptr;
	if (!otool.offset_handler)
		otool.offset_handler = offset_handler;
	return (&otool);
}
