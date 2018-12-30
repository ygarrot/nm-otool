/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 14:00:39 by ygarrot           #+#    #+#             */
/*   Updated: 2018/12/30 15:52:30 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"


void	ft_del_nothing(void *why)
{
	(void)why;
	return ; 
}

void		iter_btree(t_btree **root, void *struc, void (*f)(void *, void *struc))
{
	void	*content;

	if (!root || !*root)
		return ;
	content = (*root)->item;
	if ((*root)->left)
		iter_btree(&(*root)->left, struc, f);
	if (content)
		(*f)(content, struc);
	if ((*root)->right)
		iter_btree(&(*root)->right, struc, f);
}


