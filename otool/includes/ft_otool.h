/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:32:25 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/04 12:42:08 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "./debug.h"
# include "../../libft/includes/libft.h"
# include "../../includes/ft_macho.h"

typedef	struct s_sec
{
	uintmax_t	size;
	uintmax_t	addr;
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

t_otool		*get_otool(t_otool *ptr);
void	iter_over_mem(void *ptr, void *struc, int type,
		void	(*f)(void*, void *struc, uint32_t index));
void		ranlib_handler(void *ptr, void *struc);
void		cross_symbol(void	*ptr, void	*struc, uint32_t index);
void		cross_command(void	*ptr, void	*struc, uint32_t index);
void		cross_arch(void *ptr);
#endif
