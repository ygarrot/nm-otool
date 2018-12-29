/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 14:15:01 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/29 14:36:49 by ygarrot          ###   ########.fr       */
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
 
enum
{
	BSS_ADD,
	DATA_ADD,
	TEXT_ADD
}	e_sect;

typedef struct mach_header_64				t_mach_header_64;
typedef struct load_command					t_load_command;
typedef struct symtab_command				t_symtab_command;
typedef struct section_64						t_section_64;
typedef struct segment_command_64		t_segment_command_64;
typedef struct nlist_64							t_list64;

typedef struct	s_list_temp
{
	int		symb;
	char	c;
}				t_list_temp;

typedef struct	s_nm
{
	size_t		count_sect;
	long			sect_address[TEXT_ADD + 1];
	int				opt;
}								t_nm;

void	iter_over_section(t_segment_command_64 *segm, void	*struc,
		void	(*f)(t_section_64*, t_nm *struc));
char		get_flag(t_list64 ptr, int type, t_nm *nm);
void		set_section_addresses(t_section_64 *section, t_nm	*nm);

#endif
