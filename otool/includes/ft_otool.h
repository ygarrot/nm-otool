/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:32:25 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/03 14:15:21 by ygarrot          ###   ########.fr       */
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
# include <mach-o/ranlib.h>
# include <sys/stat.h>
#define ARLIB "!<arch>\n"
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
	RANLIB_64,
	RANLIB
}	e_strcut;

#define SYM_TAB_L  888
typedef	struct s_sec
{
	int		size;
	int		addr;
	int		offset;
	unsigned char	*ptr;
}							t_sec;

typedef struct s_otool
{
	t_sec					section;
	unsigned long	magic_number;
	void		*ptr;
	int			iter_nb;
	void		*offset;
	void		*string_table;
	char			*file_name;
	t_btree		*ranlib;
	void		*header;
	int			type;
	int			(*offset_handler)(struct s_otool *ot, void *ptr, int inc_value);
	void		*symhead;
	int			vm_address;
}								t_otool;

typedef struct s_object_header {
	char        name[16];       
	char        timestamp[12];  
	char        userid[6];      
	char        groupid[6];  
	char				mode[8];
	char				size[8];
	char		    endheader[4];      
	char        longname[20];   
}											t_object_header;

typedef struct string_table {
	uint32_t       size;
	char         data[6];
}								t_string_table;

typedef struct s_symbol_info {
	uint32_t    symbol; 
	uint32_t    object;
}							t_symbol_info;

typedef struct ranlib_64						t_ranlib_64;

typedef struct 	s_symbol_table {
	uint32_t       size;  
	t_ranlib_64		ranlib;
}								t_symbol_table;

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
typedef struct ranlib								t_ranlib;


t_otool		*get_otool(t_otool *ptr);
void	iter_over_mem(void *ptr, void *struc, int type,
		void	(*f)(void*, void *struc, uint32_t index));
void		ranlib_handler(void *ptr, void *struc);
void	cross_symbol(void *ptr);
void		cross_command(void	*ptr, void	*struc, uint32_t index);
void		cross_arch(void *ptr);
#endif
