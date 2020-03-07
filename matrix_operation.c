/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 00:15:03 by nathan            #+#    #+#             */
/*   Updated: 2020/02/16 18:53:15 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firstprog.h"
#include <stdio.h>

GLfloat*	export_matrix(s_matrix* matrix)
{
	static GLfloat new_mat[16];
	int i;

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

//float		mult_vec_matric(s_vector vec, s_matrix, matrix);

s_matrix	mult_matrix(s_matrix a, s_matrix b)
{
	int firstRow = 0;
	int firstColumn = 0;
	int secondColumn = 0;
	s_matrix new_matrix = {0};

	firstRow = 0;
	while (firstRow < 4)
	{
		firstColumn = 0;
		while (firstColumn < 4)
		{
			secondColumn = 0;
			while (secondColumn < 4)
			{
				new_matrix.p[firstRow][firstColumn] += a.p[firstRow][secondColumn] * b.p[secondColumn][firstColumn];
				secondColumn++;
			}
			firstColumn++;
		}
		firstRow++;
	}
	return (new_matrix);
}

void	print_matrix(s_matrix a)
{
	int i;

	i = 0;
	while (i < 4)
	{
		printf("|%.3f |  %.3f | %.3f | %.3f|\n", a.p[i][0], a.p[i][1], a.p[i][2], a.p[i][3]);
		i++;
	}
}

s_matrix	create_proj_matrix(float fov, float aspect, float near, float far)
{
	s_matrix new_matrix;

	float tanHalfFov = tan(to_rad(fov) / 2);
	new_matrix = (s_matrix){ .p = {
		{1 / (aspect * tanHalfFov), 0 , 0, 0},
		{0, 1 / tanHalfFov, 0, 0},
		{0, 0 , -(far + near) / (far - near), (-2 * far * near) / (far - near)},
		{0, 0 , -1, 1}}
	};
	return (new_matrix);
}

s_matrix	create_x_rot_matrix(float angle)
{
	s_matrix matrix;

	matrix = (s_matrix){ .p = {
		{1, 0, 0, 0},
		{0, cos(angle), -sin(angle), 0},
		{0, sin(angle), cos(angle), 0},
		{0, 0, 0, 1}}
	};
	return (matrix);
}

s_matrix	create_y_rot_matrix(float angle)
{
	s_matrix matrix;

	matrix = (s_matrix){ .p = {
		{cos(angle), 0, sin(angle), 0},
		{0, 1, 0, 0},
		{-sin(angle), 0, cos(angle), 0},
		{0, 0, 0, 1}}
	};
	return (matrix);
}

s_matrix	create_z_rot_matrix(float angle)
{
	s_matrix matrix;

	matrix = (s_matrix){ .p = {
		{cos(angle), -sin(angle), 0, 0},
		{sin(angle), cos(angle), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}}
	};
	return (matrix);
}

s_matrix	create_translation_matrix(float x, float y, float z)
{
	s_matrix matrix;

	matrix = (s_matrix){ .p = {
		{1, 0, 0, x},
		{0, 1, 0, y},
		{0, 0, 1, z},
		{0, 0, 0, 1}}
	};
	return (matrix);
}

s_matrix	create_scale_matrix(float x, float y, float z)
{
	s_matrix matrix;

	matrix = (s_matrix){ .p = {
		{x == 0 ? 1 : x, 0, 0, 0},
		{0, y == 0 ? 1 : y, 0, 0},
		{0, 0, z == 0 ? 1 : z, 0},
		{0, 0, 0, 1}}
	};
	return (matrix);
}

s_matrix	new_matrix()
{
	s_matrix matrix;

	matrix = (s_matrix){ .p = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}}
	};
	return (matrix);
}
