/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 17:39:02 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/04 16:27:31 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_otool.h"

int			get_symtab_size(char *ptr)
{
		char **str = ft_strsplit(ptr, ' ');
		if (ft_tablen(str) < 5)
			return (INT_MAX);
		int size = ft_atoi(str[5]);
		ft_free_dblechar_tab(str);
		return (size + 60);
}

void	cross_symbol(void *ptr, void *struc, uint32_t index)
{
	t_otool		*otool;
	char 		*str;
	char		*file;
	int			len;

	(void)index;
	otool = struc;
	str = ptr;
	file = &str[ft_strlento(str, '\n') +1];
	ft_printf("%s(%s):\n", otool->file_name,file); 
	len = ft_strlen(str);
	while (!str[len])
		len++;
/* TODO : check offset */
	cross_arch(str + len);
}
int ft_memalign(int size, int alignment)
{
	return ((size + alignment) & (~alignment));
}
void	ranlib_handler(void *ptr, void *struc)
{
	t_otool *otool;
	char **tab; 
	unsigned char *strr;
	t_symbol_table *table; 

	otool = struc;
	tab = ft_strsplit((char*)ptr + 8, ' ');
	strr = (unsigned char*)ptr + 8 + ft_strlen((char*)ptr + 4) ;
	table = (void*)strr;
	otool->iter_nb = table->size / sizeof(t_symbol_info);
	otool->symhead = ptr;
	otool->string_table = (void*)table + table->size;
	otool->type = RANLIB_64;
	iter_over_mem(ptr + 68 + ft_atoi(tab[5]), otool, SYM_TAB_L, &cross_symbol);
}
