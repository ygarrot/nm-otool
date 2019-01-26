/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smap2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:22:10 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/26 18:13:07 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmap2(char *s, char (*f)(char*))
{
	int		i;

	i = 0;
	if (!(s || (*f)))
		return (NULL);
	while (s[i])
		i++;
	i = 0;
	while (s[i])
	{
		s[i] = f(&s[i]);
		i++;
	}
	s[i] = '\0';
	return (s);
}