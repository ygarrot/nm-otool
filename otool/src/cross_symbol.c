/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 17:39:02 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/03 14:45:32 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_otool.h"

int		offset_cmp(void *elem1, void *elem2)
{
	t_otool *otool;

	otool = get_otool(0);
	if (!elem1 || !elem2)
		return (0);
	if (otool->type == RANLIB_64)
		return (((t_symbol_info*)elem1)->object - ((t_symbol_info*)elem2)->object);
	else 
		return (((t_ranlib*)elem1)->ran_un.ran_strx - ((t_ranlib*)elem2)->ran_off);
}

void	cross_symbol(void *ptr)
{
	t_symbol_info *sym;
	t_otool		*otool = get_otool(0);
	char		*file;


	sym = (t_symbol_info*)ptr;
	t_object_header *obj ; 
	obj= (t_object_header*)ptr;
	ft_printf("%llx\n", sym->object );
		ft_printf("symhead: %p\n", otool->symhead);
	char *str = otool->symhead + (sym->object);
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
	ft_printf("elem2: %llx\n", ((t_symbol_info*)ptr)->object);
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
		otool->string_table = (void*)table + table->size;
	otool->type = RANLIB_64;
	iter_over_mem(&table->ranlib, otool, SYM_TAB_L, &tree_sort);
	btree_apply_infix(otool->ranlib, cross_symbol);
}
