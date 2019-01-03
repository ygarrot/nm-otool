/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 17:39:02 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/03 14:18:00 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_otool.h"

int		offset_cmp(void *elem1, void *elem2)
{
	t_otool *otool;

	otool = get_otool(0);
	if (otool->type == RANLIB_64)
		return (((t_ranlib_64*)elem1)->ran_un.ran_strx - ((t_ranlib_64*)elem2)->ran_un.ran_strx);
	else 
		return (((t_ranlib*)elem1)->ran_un.ran_strx - ((t_ranlib*)elem2)->ran_off);
}

void	cross_symbol(void *ptr)
{
	t_ranlib_64 *sym;
	t_otool		*otool = get_otool(0);
	char		*file;


	sym = (t_ranlib_64*)ptr;
	t_object_header *obj ; 
	obj= (t_object_header*)ptr;
	ft_printf("%llx\n", sym->ran_un.ran_strx & 0xffff);
		ft_printf("symhead: %p\n", otool->symhead);
	char *str = otool->symhead + (sym->ran_un.ran_strx & 0xffff);
	file = &str[ft_strlento(str, '\n') +1];
	ft_printf("%s(%s)\n", otool->file_name,file); 
	(void)index;
	/* ft_printf("%s %d\n", str, sizeof(t_object_header)); */
	/* ft_printf("len : %d\n", ft_strlento(str, '\n') +1); */
	cross_arch(str + 80);
	ft_putendl("");
}

void	ft_del_nothing(void *nothing)
{
	(void)nothing;
}

void	tree_sort(void *ptr, void *struc, uint32_t index)
{

	(void)index;
	btree_insert_data(&((t_otool*)struc)->ranlib, ptr, offset_cmp, ft_del_nothing); 
}

void	ranlib_handler(void *ptr, void *struc)
{
	t_otool *otool;

	otool = struc;
	unsigned char *strr = (unsigned char*)ptr + 8 + ft_strlen((char*)ptr + 4) ;
		t_symbol_table *table = (void*)strr;
		otool->iter_nb = table->size / sizeof(t_symbol_info);
		otool->symhead = ptr;
		ft_printf("symhead: %p\n", otool->symhead);
		otool->string_table = (void*)table + table->size;

	otool->type = RANLIB_64;
	ft_printf("%d\n", table->ranlib.ran_un.ran_strx);
	iter_over_mem(&table->ranlib, otool, SYM_TAB_L, &tree_sort);
	btree_apply_infix(otool->ranlib, cross_symbol);
}
