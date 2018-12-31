/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:32:25 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/31 17:32:32 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "./debug.h"
# include "../../libft/includes/libft.h"
# include <stdlib.h>
# include <sys/mman.h>
# include <stdio.h>
# include <fcntl.h>
# include <mach-o/nlist.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <sys/stat.h>

enum
{
	MACH_HEADER,
	MACH_HEADER_64,
	LOAD_COMMAND,
	SEGMENT_COMMAND_64,
	SEGMENT_COMMAND,
	SYM_TAB,
	SECTION_64,
	SECTION,
}	e_strcut;

typedef struct fat_header 					t_fat_header;
typedef struct fat_arch 						t_fat_arch;
typedef struct mach_header				t_mach_header;
typedef struct mach_header_64				t_mach_header_64;
typedef struct load_command					t_load_command;
typedef struct symtab_command				t_symtab_command;
typedef struct section_64						t_section_64;
typedef struct section							t_section;
typedef struct segment_command			t_segment_command;
typedef struct segment_command_64		t_segment_command_64;
typedef struct nlist_64							t_list64;
typedef struct nlist								t_nlist;


void	iter_over_mem(void *ptr, void *struc, int type,
		void	(*f)(void*, void *struc, uint32_t index));
void		cross_command(void	*ptr, void	*struc, uint32_t index);
void		cross_arch(void *ptr);
#endif
