/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 12:18:56 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/30 12:23:54 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

uint32_t		command_64(t_mach_header_64 *ptr)
{
	return (((t_mach_header_64*)ptr)->ncmds);
}

int		sym_tab_64(t_mach_header_64 *ptr)
{
			return ((t_mach_header_64*)ptr->nsyms);
}

int	secion_64(t_segment_command_64)
{
			return ((t_segment_command_64*)ptr->nsects);
}
