/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 14:15:01 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/28 17:08:11 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "../../libft/includes/libft.h"
# include <stdlib.h>
# include <sys/mman.h>
# include <stdio.h>
# include <fcntl.h>
# include <mach-o/nlist.h>
# include <mach-o/loader.h>
# include <sys/stat.h>

typedef struct section_64 t_section_64;
typedef struct	segment_command_64 t_segment_command_64;
typedef struct nlist_64 t_list64;

typedef struct s_list_temp
{
	int		symb;
	char	c;
}												t_list_temp;

typedef struct s_nm
{
	long			sect_adress[10];
	int		opt;
}							t_nm;
 
enum
{
	O_FKA	


}opt;

void		iter_over_section(t_segment_command_64 *segm);
char		get_flag(t_list64 ptr, int type);

#endif
