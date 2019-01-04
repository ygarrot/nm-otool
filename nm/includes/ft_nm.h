/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 14:15:01 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/04 12:44:25 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "./debug.h"
# include "../../libft/includes/libft.h"
#include "../../includes/ft_macho.h"

enum
{
	BSS_ADD,
	DATA_ADD,
	TEXT_ADD
}	e_sect;

typedef struct	s_list_temp
{
	int		symb;
	char	c;
}				t_list_temp;

typedef struct s_fat_h
{
	void	*header;
	int		narch;
}								t_fat_h;

typedef struct	s_nm
{
	t_fat_h fat_h;
	size_t		count_sect;
	char			*string_table;
	long			sect_address[TEXT_ADD + 1];
	t_btree		*btree;
	int				iter_nb;
	int				opt;
	unsigned int				current_arch;
	void *header;
}								t_nm;

void	btree_erase(t_btree **root, void *erase(void **));
void	iter_over_section(t_segment_command_64 *segm, void	*struc,
		void	(*f)(t_section_64*, void *ptr, uint32_t index));
void	apply_symtab(t_symtab_command *sym, t_nm *nm);
char		get_flag(t_list64 ptr, int type, t_nm *nm);
void		print_nm_format(void *ptr, void *nm);
void		set_section_addresses(void *section, void *ptr, uint32_t index);
void		iter_btree(t_btree **root, void *struc, void (*f)(void *, void *struc));
void		*ft_del_nothing_2(void **why);
void		ft_del_nothing(void *why);
void	iter_over_mem(void *ptr, void *struc, int type,
		void	(*f)(void*, void *struc, uint32_t index));
int		ft_alphacmp(void *s1, void *s2);
t_nm		*get_nm(t_nm *nm);
void	print_output(int nsyms, int symoff, t_nm *nm);
void		cross_command(void	*ptr, void	*struc, uint32_t index);
void		cross_arch(void *ptr);
#endif
