/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 19:28:55 by nathan            #+#    #+#             */
/*   Updated: 2021/01/13 10:56:15 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <assert.h>

extern void			copy_triangles(int end_index, int *dest, int *src)
{
	int i;
	int j;
	int first_point;

	i = 0;
	j = 1;
	first_point = src[0];
	while (i < end_index)
	{
		dest[i] = first_point;
		i++;
		dest[i] = src[j];
		i++;
		j++;
		dest[i] = src[j];
		i++;
	}
}

extern void			load_triangles(char *buf, int index[4], int *index_found)
{
	*index_found = 0;
	while (*buf)
	{
		while (*buf && !ft_isdigit(*buf))
			buf++;
		if (ft_isdigit(*buf))
		{
			assert(*index_found < 4);
			index[*index_found] = atoi(buf) - 1;
			*index_found = *index_found + 1;
		}
		while (*buf && *buf != ' ')
			buf++;
	}
	assert(*index_found >= 3);
}
