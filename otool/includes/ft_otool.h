/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:32:25 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/28 14:26:24 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "../../libft/includes/libft.h"
# include "../../includes/ft_macho.h"

typedef struct s_otool	t_otool;

typedef struct	s_cpu_family
{
	const int	type;
	const char	*name;
	const char	*print_format;
	void		(*print_func)(unsigned char *ptr, int index);
}				t_cpu_family;

typedef struct	s_sec
{
	unsigned char	*ptr;
	uintmax_t		size;
	uintmax_t		addr;
	int				offset;
}				t_sec;

struct			s_otool
{
	t_sec				section;
	t_file_attribute	file;
	t_head_utils		head;
	t_symtab_utils		symtab;
	t_mem_utils			mem;
	int					error;
	int					(*offset_handler)(struct s_otool *ot,
	void *ptr, int inc_value);
};

t_otool			*get_otool(t_otool *ptr);
t_cpu_family	get_cpu_family(cpu_type_t type, cpu_subtype_t subtype);
void			is_fat_header(void *ptr, void *otool);
void			handle_header64(void *ptr, void *otool);
void			handle_header32(void *ptr, void *otool);
void			ranlib_handler(void *ptr, void *struc);
void			iter_over_mem(void *ptr, void *struc, int type,
				void (*f)(void *, void *struc, uint32_t index));
void			cross_symbol(void *ptr, void *struc, uint32_t index);
void			print_otool(void *ptr, void *struc, uint32_t index);
void			set_section_values(void *ptr, t_otool *otool);
void			cross_command(void *ptr, void *struc, uint32_t index);
void			print_32(unsigned char *ptr, int i);
void			print_64(unsigned char *ptr, int i);
void			set_otool(t_otool *otool, void *ptr);
char			*print_arch(char *r, void *ptr);
long			get_int_endian(t_otool *otool, long to_convert);
int				is_text_sect(void *sect, unsigned int arch_type);
int				cross_arch(void *ptr, char *file_name);
int				is_section_type(t_section *section, char *type);
int				is_section64_type(t_section_64 *section64, char *type);
int				is_segment_type(t_section *section, char *type);
int				is_segment64_type(t_section_64 *section64, char *type);
int				ft_error(char *file, char *str);
#endif
