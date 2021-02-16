/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 19:28:55 by nathan            #+#    #+#             */
/*   Updated: 2021/02/16 05:11:08 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <assert.h>
#include <float.h>
#include <math.h>

static const char	*ftoi_assign(const char *str, float *assign, double d)
{
	float	sign;
	int		point_found;
	int		e;

	sign = 1;
	e = 0;
	point_found = 0;
	if (*str == '-' && str++ && (sign = 1))
		sign *= -1;
	while (ft_isdigit(*str) || *str == '.')
	{
		if (*str == '.' && ++point_found && str++)
			continue;
		if (point_found)
			e--;
		d = d * 10.0 + (*str - '0');
		str++;
	}
	while (e++ < 0)
		d *= 0.1;
	*assign = (*str == ' ' || *str == '\0' || *str == '\r') ?
		(float)(d * sign) : NAN;
	*assign = (point_found > 1) ? NAN : *assign;
	return (str);
}

int					scop_sscanf(const char *str, float f[3])
{
	int	i;

	i = 0;
	if (str[0] != 'v' || str[1] != ' ')
		return (0);
	while (*str == 'v' || *str == ' ')
		str++;
	str = ftoi_assign(str, &f[0], 0.0);
	if (*str != ' ')
		return (0);
	str = ftoi_assign(str + 1, &f[1], 0.0);
	if (*str != ' ')
		return (0);
	str = ftoi_assign(str + 1, &f[2], 0.0);
	while (i < 3)
	{
		if (f[i] != f[i])
			return (0);
		i++;
	}
	return (1);
}

t_vector			center_model_mat(t_parsed_data *parsed_data)
{
	int		i;
	int		j;
	float	min[3];
	float	max[3];

	min[0] = FLT_MAX;
	min[1] = FLT_MAX;
	min[2] = FLT_MAX;
	max[0] = -FLT_MAX;
	max[1] = -FLT_MAX;
	max[2] = -FLT_MAX;
	i = -1;
	while (++i < parsed_data->nb_points && (j = -1))
		while (++j < 3)
		{
			if (min[j] > parsed_data->data[i * 5 + j])
				min[j] = parsed_data->data[i * 5 + j];
			if (max[j] < parsed_data->data[i * 5 + j])
				max[j] = parsed_data->data[i * 5 + j];
		}
	return ((t_vector){(max[0] - min[0]) / -2.f - min[0],
			(max[1] - min[1]) / -2.f - min[1],
			(max[2] - min[2]) / -2.f - min[2], 1.0f});
}

void				copy_triangles(int end_index, int *dest, int *src)
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

void				load_triangles(char *buf, int index[4], int *index_found)
{
	int		atoi_value;

	*index_found = 0;
	while (*buf)
	{
		while (*buf && !ft_isdigit(*buf))
			buf++;
		if (ft_isdigit(*buf))
		{
			assert(*index_found < MAX_POINTS_PER_FACE);
			atoi_value = atoi(buf);
			assert(atoi_value && "face index shouln't be equal to 0");
			index[*index_found] = atoi_value - 1;
			*index_found = *index_found + 1;
		}
		while (*buf && *buf != ' ')
			buf++;
	}
	assert(*index_found >= 3);
}
