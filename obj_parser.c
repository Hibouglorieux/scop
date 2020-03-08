/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:37:02 by nathan            #+#    #+#             */
/*   Updated: 2020/03/08 17:25:49 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firstprog.h"
#include <assert.h>
#include <stdio.h> // sscanf
#include <fcntl.h> //open / close

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
	assert((ptr = malloc(sizeof(float) * (parse_data->nb_points + 3))) != NULL);
	i = 0;
	while (i < parse_data->nb_points)
	{
		ptr[i] = parse_data->points_data[i];
		i++;
	}
	j = 0;
	while (j < 3)
		ptr[i++] = f[j++];
	parse_data->nb_points += 3;
	free(parse_data->points_data);
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

	parse_data = (s_parsing){0, NULL, 0, NULL};
	assert((fd = open(path_to_file, O_RDONLY)) != -1);
	while (get_next_line(fd, &buf))
	{
		update_parse_data(&parse_data, buf);
	}
//	print_parse_data(&parse_data); free(buf);
	close(fd);
	return (parse_data);
}
