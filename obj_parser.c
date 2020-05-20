/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:37:02 by nathan            #+#    #+#             */
/*   Updated: 2020/04/09 23:58:28 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firstprog.h"
#include <assert.h>
#include <stdio.h> // sscanf
#include <fcntl.h> //open / close
#include <float.h>

void	define_min_max_inside_face(s_vec2* min, s_vec2* max, int current_face, const s_parsing* parse_data, int starting_triangle_index)
{
	int		i;
	int		index;
	int		j;

	i = 0;
	min->x = FLT_MAX;
	min->y = FLT_MAX;
	max->x = FLT_MIN;
	max->y = FLT_MIN;
	starting_triangle_index *= 3;
	//3 points per triangle
	while (i < parse_data->triangle_per_face[current_face])
	{
		printf("current_face:%d\n", parse_data->triangle_per_face[current_face]);
		printf("current_face:%d\n", current_face);
		index = i * 3 + starting_triangle_index;
		// where am (i * 3(points)) + starting triangle 
		// example: tri_data[2] is 0 1 2, i want to analyze point 
		j = i == 0 ? 0 : 1; // we already did 1 first point
		while (j < 3)
		{
			//printf("nb_points:%d nb_of_triangles:%d nb_of_faces:%d, index + j:%d\n", 
					//parse_data->nb_points, parse_data->nb_of_triangles, parse_data->nb_of_faces, index + j);
			if (parse_data->points_data[parse_data->triangles_data[index + j]] < min->x)
				min->x = parse_data->points_data[parse_data->triangles_data[index + j]];
			if (parse_data->points_data[parse_data->triangles_data[index + j]] > max->x)
				max->x = parse_data->points_data[parse_data->triangles_data[index + j]];
			if (parse_data->points_data[parse_data->triangles_data[index + j] + 1] < min->y)
				min->y = parse_data->points_data[parse_data->triangles_data[index + j] + 1];
			if (parse_data->points_data[parse_data->triangles_data[index + j] + 1] > max->y)
				max->y = parse_data->points_data[parse_data->triangles_data[index + j] + 1];
			j++;
		}
		i++;
	}
}

float* create_faces_data(const s_parsing* parse_data)
{
	float*		texture_points;
	s_vec2		min;
	s_vec2		max;
	int			i;
	int			j;
	int			k;
	int			triangle_count;

	triangle_count = 0;
	assert((texture_points = malloc(sizeof(float) * 2 * parse_data->nb_of_triangles * 3)) != NULL);
	i = 0;
	while (i < parse_data->nb_of_faces)
	{
		define_min_max_inside_face(&min, &max, i, parse_data, triangle_count);
		j = 0;
		while (j < parse_data->triangle_per_face[i])
		{
			s_vec2 length = {
				.x = max.x - min.x,
				.y = max.y - min.y
			};
			k = 0;
			while (k < 3)
			{
				s_vec2 actual_point = {
					parse_data->points_data[parse_data->triangles_data[triangle_count + j * 3 + k]],
					parse_data->points_data[parse_data->triangles_data[triangle_count + j * 3 + k] + 1]
				};
				texture_points[j * 2 + triangle_count * 3 * 2] = actual_point.x - min.x / length.x;
				texture_points[j * 2 + 1 + triangle_count * 3 * 2] = actual_point.y - min.y / length.y;
				k++;
			}
			j++;
		}
		triangle_count += parse_data->triangle_per_face[i];
		i++;
	}
	return (texture_points);
}

void	update_faces(s_parsing* parse_data, int nb_of_triangles)
{
	int*	ptr;
	int		i;

	assert((ptr = malloc(sizeof(int) * parse_data->nb_of_faces + 1)) != NULL);
	i = 0;
	while (i < parse_data->nb_of_faces)
	{
		ptr[i] = parse_data->triangle_per_face[i];
		i++;
	}
	free(parse_data->triangle_per_face);
	parse_data->triangle_per_face = ptr;
	parse_data->triangle_per_face[parse_data->nb_of_faces] = nb_of_triangles;
	parse_data->nb_of_faces++;
}

void copy_triangles(int end_index, GLuint* dest, int* src)
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

void	add_triangles(s_parsing* parse_data, char* buf)
{
	int		index[4];
	GLuint	*ptr;
	int		index_found;
	int		i;

	index_found = 0;
	while (*buf)
	{
		while (*buf && !ft_isdigit(*buf))
			buf++;
		if (ft_isdigit(*buf))
		{
			assert(index_found < 4);
			index[index_found] = atoi(buf) - 1;
			index_found++;

		}
		while (*buf && *buf != ' ')
			buf++;
	}
	assert(index_found >= 3);
	assert((ptr = malloc(sizeof(int) * (parse_data->nb_of_triangles + (index_found - 2) * 3))) != NULL);
	i = 0;
	while (i < parse_data->nb_of_triangles)
	{
		ptr[i] = parse_data->triangles_data[i];
		i++;
	}
	copy_triangles((index_found - 2) * 3, &ptr[parse_data->nb_of_triangles], index);
	parse_data->nb_of_triangles += ((index_found - 2) * 3);
	update_faces(parse_data, (index_found - 2));
	free(parse_data->triangles_data);
	parse_data->triangles_data = ptr;
}

void	add_points(s_parsing* parse_data, char* buf)
{
	float	f[3];
	float	*ptr;
	int		i;
	int		j;

	assert(sscanf(buf, "v %f %f %f", &f[0], &f[1], &f[2]) == 3);
	assert((ptr = malloc(sizeof(float) * parse_data->nb_points * 3 + 3)) != NULL);
	i = 0;
	while (i < parse_data->nb_points)
	{
		ptr[i] = parse_data->points_data[i];
		i++;
	}
	j = 0;
	while (j < 3)
		ptr[i++] = f[j++];
	free(parse_data->points_data);
	parse_data->nb_points++;
	parse_data->points_data = ptr;
}

void	update_parse_data(s_parsing* parse_data, char* buf)
{
	if (buf[0] == '#')
		return;
	if (buf[0] == 'v' && buf[1] == ' ')
	{
		add_points(parse_data, buf);
	}
	if (buf[0] == 'f' && buf[1] == ' ')
	{
		add_triangles(parse_data, buf);
	}
}

void	print_parse_data(s_parsing* parse_data)
{
	for (int i = 0; i < parse_data->nb_points; i+=3)
	{
		printf("point number:%d x:%f y:%f z:%f\n", i/3, parse_data->points_data[i], parse_data->points_data[i+1], parse_data->points_data[i+2]);
	}
	for (int i = 0; i < parse_data->nb_of_triangles; i+=3)
	{
		printf("A:%d B:%d C:%d\n", parse_data->triangles_data[i], parse_data->triangles_data[i+1], parse_data->triangles_data[i+2]);
	}
}
s_parsing	ft_parse_file(char* path_to_file)
{
	char*		buf;
	int			fd;
	s_parsing	parse_data;

	parse_data = (s_parsing){0, NULL, 0, NULL, 0, NULL, NULL};
	assert((fd = open(path_to_file, O_RDONLY)) != -1);
	while (get_next_line(fd, &buf))
	{
		update_parse_data(&parse_data, buf);
	}
	parse_data.texture_data = create_faces_data(&parse_data);
//	print_parse_data(&parse_data); free(buf);
	close(fd);
	return (parse_data);
}
