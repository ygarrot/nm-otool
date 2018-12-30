/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 14:15:01 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/30 17:16:01 by ygarrot          ###   ########.fr       */
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

enum
{
	MACH_HEADER_64,
	LOAD_COMMAND,
	SEGMENT_COMMAND_64,
	SEGMENT_COMMAND,
	SYM_TAB,
	SECTION_64,
	SECTION,
}	e_strcut;

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
	char			*string_table;
	long			sect_address[TEXT_ADD + 1];
	t_btree		*btree;
	int				iter_nb;
	int				opt;
	void *header;
}								t_nm;

void	iter_over_section(t_segment_command_64 *segm, void	*struc,
		void	(*f)(t_section_64*, void *ptr, uint32_t index));
void	apply_symtab(t_symtab_command *sym, t_nm *nm);
char		get_flag(t_list64 ptr, int type, t_nm *nm);
void		print_nm_format(void *ptr, void *nm);
void		set_section_addresses(void *section, void *ptr, uint32_t index);
void		iter_btree(t_btree **root, void *struc, void (*f)(void *, void *struc));
void		ft_del_nothing(void *why);
void	iter_over_mem(void *ptr, void *struc, int type,
		void	(*f)(void*, void *struc, uint32_t index));
int		ft_alphacmp(void *s1, void *s2);
t_nm		*get_nm(t_nm *nm);
void	print_output(int nsyms, int symoff, t_nm *nm);
void		cross_command(void	*ptr, void	*struc, uint32_t index);
#endif
