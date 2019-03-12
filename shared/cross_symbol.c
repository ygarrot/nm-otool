/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 14:05:34 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/12 14:28:26 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_macho.h"

int		get_symtab_size(char *ptr)
{
	char	**str;
	int		size;

	str = ft_strsplit(ptr, ' ');
	if (ft_tablen(str) < 5)
		return (INT_MAX);
	size = ft_atoi(str[5]);
	ft_free_dblechar_tab(str);
	return (size + 60);
}

void	cross_symbol(void *ptr, void *struc, uint32_t index)
{
	t_macho	*macho;
	char	*str;
	char	*file;
	int		len;

	(void)index;
	macho = struc;
	str = ptr;
	file = &str[ft_strlento(str, '\n') + 1];
	if ((macho->head.arch_offset && ptr > macho->head.arch_offset)
	|| !ft_strlen(file))
	{
		macho->error = 2;
		return ;
	}
	ft_printf("\n%s(%s):\n", macho->file.name, file);
	len = ft_strlen(str);
	while (!str[len] && !macho->offset_handler(macho, str, len + 1))
		len++;
	if (macho->offset_handler(macho, str, len))
		return ;
	cross_arch(str + len, 0);
}


int		ft_memalign(int size, int aligotoolent)
{
	return ((size + aligotoolent) & (~aligotoolent));
}

void	ranlib_handler(void *ptr, t_macho *macho)
{
	char			**tab;
	unsigned char	*strr;
	t_symbol_table	*table;
	int				size;

	tab = ft_strsplit((char *)ptr + 8, ' ');
	strr = (unsigned char *)ptr + 8 + ft_strlen((char *)ptr + 4);
	table = (void *)strr;
	macho->mem.iter_nb = table->size / sizeof(t_symbol_info);
	macho->symtab.symhead = ptr;
	macho->head.type = RANLIB_64;
	size = ft_atoi(tab[5]);
	ft_free_dblechar_tab(tab);
	macho->symtab.active = true;
	iter_over_mem(ptr + 68 + size, macho, SYM_TAB_L, &cross_symbol);
	macho->symtab.active = false;
}
