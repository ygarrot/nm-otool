/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 10:50:18 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/23 18:48:02 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>

intmax_t	ft_swap_int(intmax_t num, int size)
{
	intmax_t i;
	intmax_t ret;

	i = -1;
	while (++i < size)
	{
		ret = (num >> (i * 8)) & (1 << (i * num));
	}
	return ret;
}

#include <stdio.h>
int main(void)
{
	
	int t  = 63;
		printf("%d\n", (int)ft_swap_int(63, sizeof(int)));
}
