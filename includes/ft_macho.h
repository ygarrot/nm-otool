/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_macho.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 12:30:12 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/28 14:04:19 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MACHO_H
# define FT_MACHO_H

# include <stdlib.h>
# include <sys/mman.h>
# include <stdio.h>
# include <fcntl.h>
# include <mach-o/nlist.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <mach-o/arch.h>
# include <mach/machine.h>
# include <sys/stat.h>

# define ARLIB "!<arch>\n"
# define FT_EISDIR "Is a directory"
# define NOTOBJ "is not an object file"
# define SYM_TAB_L  888
# define FT_ENOENT "No such file or directory"
# define NOT_MACHO "Object is not a Mach-O file type."

typedef struct ranlib_64				t_ranlib_64;
typedef struct fat_header				t_fat_header;
typedef struct fat_arch					t_fat_arch;
typedef struct mach_header				t_mach_header;
typedef struct mach_header_64			t_mach_header_64;
typedef struct load_command				t_load_command;
typedef struct symtab_command			t_symtab_command;
typedef struct section_64				t_section_64;
typedef struct section					t_section;
typedef struct segment_command			t_segment_command;
typedef struct segment_command_64		t_segment_command_64;
typedef struct nlist_64					t_list64;
typedef struct nlist					t_nlist;
typedef struct ranlib					t_ranlib;

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

typedef struct	s_object_header
{
	char				name[16];
	char				timestamp[12];
	char				userid[6];
	char				groupid[6];
	char				mode[8];
	char				size[8];
	char				endheader[4];
	char				longname[20];
}				t_object_header;

typedef struct	s_string_table
{
	uint32_t		size;
	char			data[6];
}				t_string_table;

typedef struct	s_file_attribute
{
	char	*name;
	size_t	size;
	int		ac;
	void	*offset;
}				t_file_attribute;

typedef struct	s_symbol_info
{
	uint32_t		symbol;
	uint32_t		object;
}				t_symbol_info;

typedef struct	s_fat_h
{
	void	*header;
	int		narch;
}				t_fat_h;

typedef struct	s_symtab_utils
{
	void		*symhead;
	bool		active;
}				t_symtab_utils;

typedef struct	s_head_utils
{
	bool			active;
	int				no_arch;
	unsigned long	magic;
	void			*ptr;
	int				type;
	void			*string_table;
	cpu_type_t		cpu_type;
	cpu_subtype_t	cpu_subtype;
}				t_head_utils;

typedef struct	s_mem_utils
{
	bool	is_big_endian;
	int		iter_nb;
}				t_mem_utils;

typedef struct	s_symbol_table {
	uint32_t		size;
	t_symbol_info	ranlib;
}				t_symbol_table;

#endif
