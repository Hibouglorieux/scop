/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:37:02 by nathan            #+#    #+#             */
/*   Updated: 2020/03/07 21:12:56 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firstprog.h"
#include <assert.h>
#include <stdio.h> // sscanf
#include <fcntl.h> //open / close

void	add_triangles(s_parsing* parse_data, char* buf)
{
	int		index[4];
	int		*ptr;
	int		index_found;
	int		i;
	int		j;

	index_found = 0;
	while (*buf)
	{
		while (*buf && !ft_isdigit(*buf))
			buf++;
		if (ft_isdigit(*buf))
		{
			assert(index_found < 4);
			index[index_found] = atoi(buf);
			index_found++;
		}
		while (*buf && *buf != ' ')
			buf++;
	}
	assert(index_found >= 3);
	assert((ptr = malloc(sizeof(int) * (parse_data->nb_of_triangles + index_found))) != NULL);
	i = 0;
	while (i < parse_data->nb_of_triangles)
	{
		ptr[i] = parse_data->triangles_data[i];
		i++;
	}
	j = 0;
	while (j < index_found)
		ptr[i++] = index[j++];
	parse_data->nb_of_triangles += index_found;
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
	free(buf);
	close(fd);
	return (parse_data);
}
