/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:32:25 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/24 14:20:06 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "./debug.h"
# include "../../libft/includes/libft.h"
# include "../../includes/ft_macho.h"

typedef struct s_otool t_otool;

typedef struct s_cpu_family
{
		int		type;
		char	*name;
		char	*print_format;
		void	(*print_func)(unsigned char *ptr, int index);
}							t_cpu_family;

typedef	struct s_sec
{
	uintmax_t	size;
	uintmax_t	addr;
	int		offset;
	unsigned char	*ptr;
}							t_sec;

typedef struct s_head_utils
{
	int			no_arch;
	unsigned long	magic;
	void		*ptr;
	int			type;
	void		*string_table;
	int			cputype;
}								t_head_utils;

typedef struct s_file_attribute
{
	char			*name;
	void		*offset;
}								t_file_attribute;

typedef struct s_symtab_utils
{
	void		*symhead;
}								t_symtab_utils;

typedef struct s_mem_utils
{
	bool	is_big_endian;
	int			iter_nb;
}								t_mem_utils;

struct s_otool
{
	int			error;
	int			(*offset_handler)(struct s_otool *ot, void *ptr, int inc_value);
	t_sec					section;
	t_file_attribute file;
	t_head_utils			head;
	t_symtab_utils		symtab;
	t_mem_utils			mem;
};

void	is_fat_header(void *ptr, void *otool);
void	handle_header64(void *ptr, void *otool);
void	handle_header32(void *ptr, void *otool);
t_otool		*get_otool(t_otool *ptr);
void	iter_over_mem(void *ptr, void *struc, int type,
		void	(*f)(void*, void *struc, uint32_t index));
t_cpu_family get_cpu_family(int type );
void		ranlib_handler(void *ptr, void *struc);
void		cross_symbol(void	*ptr, void	*struc, uint32_t index);
void	print_otool(void *ptr, void *struc, uint32_t index);
void		set_section_values(void *ptr, t_otool *otool);
void		cross_command(void	*ptr, void	*struc, uint32_t index);
int		cross_arch(void *ptr, char *file_name);
int		is_section_type(t_section *section, char *type);
int		is_section64_type(t_section_64	*section64, char *type);
int		is_segment_type(t_section *section, char *type);
int		is_segment64_type(t_section_64	*section64, char *type);
void	print_32(unsigned char *ptr, int i);
void	print_64(unsigned char *ptr, int i);
char		*print_arch(char *r, void *ptr);
int		is_text_sect(void *sect, unsigned int arch_type);
long		get_int_indian(t_otool *otool, long to_convert);
#endif
