/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fstat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 12:11:41 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/04 12:17:33 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>

int is_regular_file(int fd)
{
	struct stat path_stat;
	fstat(fd, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

