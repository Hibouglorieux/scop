/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 19:28:55 by nathan            #+#    #+#             */
/*   Updated: 2021/02/02 22:45:36 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <assert.h>
#include <float.h>

extern t_matrix		center_model_mat(t_parsed_data *parsed_data)
{
	int		i;
	int		j;
	float	min[3];
	float	max[3];

	min[0] = FLT_MAX;
	min[1] = FLT_MAX;
	min[2] = FLT_MAX;
	max[0] = FLT_MIN;
	max[1] = FLT_MIN;
	max[2] = FLT_MIN;
	i = -1;
	while (++i < parsed_data->nb_points && (j = -1))
		while (++j < 3)
		{
			if (min[j] > parsed_data->data[i * 5 + j])
				min[j] = parsed_data->data[i * 5 + j];
			if (max[j] < parsed_data->data[i * 5 + j])
				max[j] = parsed_data->data[i * 5 + j];
		}
	return (create_translation_matrix((max[0] - min[0]) / -2.f - min[0],
				(max[1] - min[1]) / -2.f - min[1],
				(max[2] - min[2]) / -2.f - min[2]));
}

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
