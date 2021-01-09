/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:37:02 by nathan            #+#    #+#             */
/*   Updated: 2021/01/08 23:52:19 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firstprog.h"
#include <assert.h>
#include <stdio.h> // sscanf
#include <fcntl.h> //open / close
#include <float.h>


void copy_triangles(int end_index, int* dest, int* src)
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

static void intialize_triangles_data(char* buf, s_internal_tmp_parsing* int_parse_data)
{
	int		index[4];
	int*	ptr;
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
	assert((ptr = malloc(sizeof(int) * (int_parse_data->nb_triangles * 3 + (index_found - 2) * 3))) != NULL);
	i = 0;
	while (i < int_parse_data->nb_triangles * 3)
	{
		ptr[i] = int_parse_data->points_index[i];
		i++;
	}
	copy_triangles((index_found - 2) * 3, &ptr[i], index);
	int_parse_data->nb_triangles += (index_found - 2);
	free(int_parse_data->points_index);
	int_parse_data->points_index = ptr;
	//printf("i saved : %d %d %d value", ptr[i], ptr[i + 1], [
}

static void load_raw_points(char* buf, s_internal_tmp_parsing* int_parse_data)
{
	float	f[3];
	float	*ptr;
	int		i;
	int		j;

	assert(sscanf(buf, "v %f %f %f", &f[0], &f[1], &f[2]) == 3);
	assert((ptr = malloc(sizeof(float) * (int_parse_data->nb_unique_points * 3 + 3))) != NULL);
	i = 0;
	while (i < int_parse_data->nb_unique_points)
	{
		ptr[i * 3] = int_parse_data->raw_points[i * 3];
		ptr[i * 3 + 1] = int_parse_data->raw_points[i * 3 + 1];
		ptr[i * 3 + 2] = int_parse_data->raw_points[i * 3 + 2];
		i++;
	}
	j = 0;
	while (j < 3)
	{
		ptr[i * 3 + j] = f[j];
		j++;
	}
	free(int_parse_data->raw_points);
	int_parse_data->nb_unique_points++;
	int_parse_data->raw_points = ptr;
}

static s_internal_tmp_parsing initialize_internal_data(char* path_to_file)
{	
	int fd;
	char* buf;

	assert((fd = open(path_to_file, O_RDONLY)) != -1);
	s_internal_tmp_parsing int_parse_data = {NULL, 0, 0, NULL};
	while (get_next_line(fd, &buf))
	{
		if (buf[0] == 'f')
			intialize_triangles_data(buf, &int_parse_data);
		if (buf[0] == 'v' && buf[1] == ' ')
			load_raw_points(buf, &int_parse_data);
		free(buf);
	}
	close(fd);
	return int_parse_data;
}

static s_parsed_data	treat_raw_data(s_internal_tmp_parsing* int_parse_data)
{
	int i;
	int	j;
	s_parsed_data exp_data;

	exp_data = (s_parsed_data){NULL, int_parse_data->nb_triangles * 3, int_parse_data->nb_triangles};
	assert((exp_data.data = malloc(sizeof(float) * exp_data.nb_points * (3/*xyz*/ + 2/*texture data*/))) != NULL);
	i = 0;
	while (i < exp_data.nb_points)
	{
		j = 0;
		while (j < 3)
		{
			exp_data.data[i * (3 + 2) + j] = int_parse_data->raw_points[int_parse_data->points_index[i] * 3 + j];
			j++;
		}
		exp_data.data[i * (3 + 2) + 3] = exp_data.data[i * (3 + 2)] + exp_data.data[i * (3 + 2) + 2];
		exp_data.data[i * (3 + 2) + 4] = exp_data.data[i * (3 + 2) + 1];
		i++;
	}
	printf("three first points\n");
	for (int j = 0; j < 3; j++)
	{
		printf("index %d .x:%f .y:%f .z:%f\n", j, exp_data.data[j * (3 + 2)], exp_data.data[j * (3 + 2) + 1], exp_data.data[j * (3 + 2) + 2]);
	}
	return (exp_data);
}


void print_intParse(s_internal_tmp_parsing* int_parse_data)
{
	printf("nb_triangles : %d, nb_unique_points:%d\n", int_parse_data->nb_triangles, int_parse_data->nb_unique_points);
	for (int i = 0; i < int_parse_data->nb_triangles * 3; i+=3)
		printf("%d triangle: %d %d %d\n", i/3, int_parse_data->points_index[i] + 1, int_parse_data->points_index[i+1] + 1,int_parse_data->points_index[i+2] + 1);
	for (int i = 0;  i < int_parse_data->nb_unique_points; i++)
	{
		printf("point %d: %f %f %f\n", i, int_parse_data->raw_points[i*3],int_parse_data->raw_points[i*3+1],int_parse_data->raw_points[i*3+ 2]);
	}
}

static void print_triangle(int i, s_parsed_data* exp_data)
{
	printf("triangle %d .x:%f  .z:%f\n", i, exp_data->data[i * (3  + 2)],exp_data->data[i * (3  + 2) + 2]);
}

static void print_exp_data(s_parsed_data* exp_data, s_internal_tmp_parsing* int_parse_data)
{
	printf("nb_triangles : %d, nb_points :%d\n", exp_data->nb_triangles, exp_data->nb_points);
	for (int i = 0; i < 3; i++)
	{
		print_triangle(int_parse_data->points_index[i], exp_data);
	}
}


s_parsed_data	parse_file(char* path_to_file)
{
	s_parsed_data	exp_data;
	s_internal_tmp_parsing int_parse_data;

	int_parse_data = initialize_internal_data(path_to_file);
	//print_intParse(&int_parse_data);
	exp_data = treat_raw_data(&int_parse_data);
	print_exp_data(&exp_data, &int_parse_data);
	free(int_parse_data.points_index);
	free(int_parse_data.raw_points);
	return (exp_data);
}
