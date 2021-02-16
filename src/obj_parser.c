/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:37:02 by nathan            #+#    #+#             */
/*   Updated: 2021/02/16 01:49:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <assert.h>
#include <fcntl.h>

static void						initialize_triangles_data(char *buf,
		t_internal_tmp_parsing *int_parse_data)
{
	int		index[4];
	int		*ptr;
	int		index_found;
	int		i;

	load_triangles(buf, index, &index_found);
	assert((ptr = malloc(sizeof(int) * (int_parse_data->nb_triangles * 3 +
						(index_found - 2) * 3))) != NULL);
	i = -1;
	while (++i < int_parse_data->nb_triangles * 3)
		ptr[i] = int_parse_data->points_index[i];
	copy_triangles((index_found - 2) * 3, &ptr[i], index);
	int_parse_data->nb_triangles += (index_found - 2);
	free(int_parse_data->points_index);
	int_parse_data->points_index = ptr;
}

static int						load_raw_points(char *buf,
		t_internal_tmp_parsing *int_parse_data)
{
	float	f[3];
	float	*ptr;
	int		i;
	int		j;

	if (!scop_sscanf(buf, f))
		return (0);
	assert((ptr = malloc(sizeof(float) * (int_parse_data->nb_unique_points
						* 3 + 3))) != NULL);
	i = 0;
	while (i < int_parse_data->nb_unique_points)
	{
		ptr[i * 3] = int_parse_data->raw_points[i * 3];
		ptr[i * 3 + 1] = int_parse_data->raw_points[i * 3 + 1];
		ptr[i * 3 + 2] = int_parse_data->raw_points[i * 3 + 2];
		i++;
	}
	j = -1;
	while (++j < 3)
		ptr[i * 3 + j] = f[j];
	free(int_parse_data->raw_points);
	int_parse_data->nb_unique_points++;
	int_parse_data->raw_points = ptr;
	return (1);
}

static t_parsed_data			treat_raw_data(
		t_internal_tmp_parsing *int_parse_data)
{
	int				i;
	int				j;
	t_parsed_data	exp_data;

	exp_data = (t_parsed_data){NULL, int_parse_data->nb_triangles * 3,
		int_parse_data->nb_triangles};
	assert((exp_data.data = malloc(sizeof(float) * exp_data.nb_points *
					(3 + 2))) != NULL);
	i = 0;
	while (i < exp_data.nb_points)
	{
		j = -1;
		assert(int_parse_data->points_index[i] < int_parse_data->
				nb_unique_points && "invalid face parsed");
		while (++j < 3)
		{
			exp_data.data[i * (3 + 2) + j] = int_parse_data->raw_points
				[int_parse_data->points_index[i] * 3 + j];
		}
		exp_data.data[i * (3 + 2) + 3] = exp_data.data[i * (3 + 2)] +
			exp_data.data[i * (3 + 2) + 2];
		exp_data.data[i * (3 + 2) + 4] = exp_data.data[i * (3 + 2) + 1];
		i++;
	}
	return (exp_data);
}

static t_internal_tmp_parsing	initialize_internal_data(char *path_to_file)
{
	int						fd;
	int						retval;
	char					*buf;
	t_internal_tmp_parsing	int_parse_data;

	assert((fd = open(path_to_file, O_RDONLY)) != -1);
	int_parse_data = (t_internal_tmp_parsing){NULL, 0, 0, NULL};
	while ((retval = get_next_line(fd, &buf)))
	{
		assert(retval != -1);
		if (buf[0] == 'f')
			initialize_triangles_data(buf, &int_parse_data);
		if (buf[0] == 'v' && buf[1] == ' ')
			assert(load_raw_points(buf, &int_parse_data) && "Parse Error");
		free(buf);
	}
	close(fd);
	return (int_parse_data);
}

t_parsed_data					parse_file(char *path_to_file)
{
	t_parsed_data			exp_data;
	t_internal_tmp_parsing	int_parse_data;

	int_parse_data = initialize_internal_data(path_to_file);
	exp_data = treat_raw_data(&int_parse_data);
	free(int_parse_data.points_index);
	free(int_parse_data.raw_points);
	return (exp_data);
}
