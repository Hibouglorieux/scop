/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 00:15:03 by nathan            #+#    #+#             */
/*   Updated: 2021/01/13 10:56:15 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLfloat		*export_matrix(t_matrix *matrix)
{
	static GLfloat	new_mat[16];
	int				i;

	i = 0;
	while (i < 4)
	{
		new_mat[i * 4 + 0] = (GLfloat)matrix->p[i][0];
		new_mat[i * 4 + 1] = (GLfloat)matrix->p[i][1];
		new_mat[i * 4 + 2] = (GLfloat)matrix->p[i][2];
		new_mat[i * 4 + 3] = (GLfloat)matrix->p[i][3];
		i++;
	}
	return (new_mat);
}

t_matrix	mult_matrix(t_matrix a, t_matrix b)
{
	int			first_row;
	int			first_column;
	int			second_column;
	t_matrix	new_matrix;

	new_matrix = (t_matrix){0};
	first_row = 0;
	while (first_row < 4)
	{
		first_column = 0;
		while (first_column < 4)
		{
			second_column = 0;
			while (second_column < 4)
			{
				new_matrix.p[first_row][first_column] += a.p[first_row]
					[second_column] * b.p[second_column][first_column];
				second_column++;
			}
			first_column++;
		}
		first_row++;
	}
	return (new_matrix);
}

t_matrix	create_x_rot_matrix(float angle)
{
	t_matrix matrix;

	matrix = (t_matrix){ .p = {
		{1, 0, 0, 0},
		{0, cos(angle), -sin(angle), 0},
		{0, sin(angle), cos(angle), 0},
		{0, 0, 0, 1}}
	};
	return (matrix);
}

t_matrix	create_y_rot_matrix(float angle)
{
	t_matrix matrix;

	matrix = (t_matrix){ .p = {
		{cos(angle), 0, sin(angle), 0},
		{0, 1, 0, 0},
		{-sin(angle), 0, cos(angle), 0},
		{0, 0, 0, 1}}
	};
	return (matrix);
}

t_matrix	create_z_rot_matrix(float angle)
{
	t_matrix matrix;

	matrix = (t_matrix){ .p = {
		{cos(angle), -sin(angle), 0, 0},
		{sin(angle), cos(angle), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}}
	};
	return (matrix);
}
