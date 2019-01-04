/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 17:39:02 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/04 11:48:54 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_otool.h"

void	cross_symbol(void *ptr, void *struc, uint32_t index)
{
	t_symbol_info *sym;
	t_otool		*otool = get_otool(0);
	char		*file;
	int			len;

	(void)struc;
	sym = (t_symbol_info*)ptr;
	t_object_header *obj ; 
	obj= (t_object_header*)ptr;
	char *str = ptr;
	file = &str[ft_strlento(str, '\n') +1];
	ft_printf("%s(%s):\n", otool->file_name,file); 
	(void)index;
	len = ft_strlen(str);
	while (!str[len])
		len++;
/* TODO : check offset */
	cross_arch(str + len);
}

void	ranlib_handler(void *ptr, void *struc)
{
	t_otool *otool;

	otool = struc;
		char **tab = ft_strsplit((char*)ptr + 8, ' ');
	unsigned char *strr = (unsigned char*)ptr + 8 + ft_strlen((char*)ptr + 4) ;
		t_symbol_table *table = (void*)strr;
		otool->iter_nb = table->size / sizeof(t_symbol_info);
		otool->symhead = ptr;
		otool->string_table = (void*)table + table->size;
	otool->type = RANLIB_64;
	otool->iter_nb = 30;
	iter_over_mem(strr - 20 + ft_atoi(tab[5]), otool, SYM_TAB_L, &cross_symbol);
}
