/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 14:15:01 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/27 19:10:39 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

#include "./debug.h"
#include "../../libft/includes/libft.h"
#include "../../includes/ft_macho.h"

enum
{
	BSS_ADD = 0,
	DATA_ADD,
	TEXT_ADD
} e_sect;

#define OPT_STR "AgnpruU"
enum
{
	PRINT_FILE_NAME = (1 << 0),
	EXTERN_ONLY = (1 << 1),
	NUMERIC_SORT = (1 << 2),
	NO_SORT = (1 << 3),
	REVERSE_SORT = (1 << 4),
	UNDEFINED_ONLY = (1 << 5),
	DEFINED_ONLY = (1 << 6)
};

typedef struct s_list_temp
{
	int symb;
	char c;
} t_list_temp;

typedef struct s_fat_h
{
	void *header;
	int narch;
} t_fat_h;

typedef struct s_file_attribute
{
	char *name;
	size_t size;
	int		ac;
	void *offset;
} t_file_attribute;

typedef struct s_mem_utils
{
	bool is_big_endian;
	int iter_nb;
} t_mem_utils;

typedef struct s_head_utils
{
	int no_arch;
	unsigned long magic;
	void *ptr;
	int type;
	void *string_table;
	int cputype;
	int cpusubtype;
} t_head_utils;

typedef struct s_cpu_family
{
	const int type;
	const char *name;
	const	int width;
	const	int mask;
	const char *print_format;
	
	// void (*print_func)(unsigned char *ptr, int index);
} t_cpu_family;

typedef struct s_symtab_utils
{
	void *symhead;
} t_symtab_utils;

typedef struct s_nm
{
	int error;
	t_mem_utils mem;
	t_head_utils head;
	t_fat_h fat_h;
	t_file_attribute file;
	int (*offset_handler)(struct s_nm *nm, void *ptr, int inc_value);
	size_t count_sect;
	long sect_address[TEXT_ADD + 1];
	t_symtab_utils symtab;
	t_btree *btree;
	int opt;
} t_nm;

void	set_nm(t_nm *nm, void *ptr);
t_cpu_family	get_cpu_family(t_nm *nm);
void is_fat_header(void *ptr, void *otool);
void handle_header64(void *ptr, void *otool);
void handle_header32(void *ptr, void *otool);
void ranlib_handler(void *ptr, void *struc);
long get_int_endian(t_nm *nm, long to_convert);
void btree_erase(t_btree **root, void *erase(void **));
void iter_over_section(t_segment_command_64 *segm, void *struc,
					   void (*f)(t_section_64 *, void *ptr, uint32_t index));
void apply_symtab(t_symtab_command *sym, t_nm *nm);
char get_flag(t_list64 ptr, int type, t_nm *nm);
void print_nm_format(void *ptr);
void set_section_addresses(void *section, void *ptr, uint32_t index);
void iter_btree(t_btree **root, void *struc, void (*f)(void *, void *struc));
void *ft_del_nothing_2(void **why);
void ft_del_nothing(void *why);
void iter_over_mem(void *ptr, void *struc, int type,
				   void (*f)(void *, void *struc, uint32_t index));
int ft_alphacmp(void *s1, void *s2);
char *print_arch(char *r, void *ptr);
t_nm *get_nm(t_nm *nm);
void print_output(int nsyms, int symoff, t_nm *nm);
void cross_command(void *ptr, void *struc, uint32_t index);
int cross_arch(void *ptr, char *file_name);
int		ft_error(char *file, char *str);
int		ft_digitcmp(void *s1, void *s2);
int		ft_nosort(void *s1, void *s2);
int		ft_sizesort(void *s1, void *s2);
#endif
