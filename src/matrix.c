/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 19:39:36 by nathan            #+#    #+#             */
/*   Updated: 2021/01/13 10:56:15 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_matrix	create_proj_matrix(float fov, float aspect, float near, float far)
{
	t_matrix	new_matrix;
	float		tan_half_fov;

	tan_half_fov = tan(to_rad(fov) / 2);
	new_matrix = (t_matrix){ .p = {
		{1 / (aspect * tan_half_fov), 0, 0, 0},
		{0, 1 / tan_half_fov, 0, 0},
		{0, 0, -(far + near) / (far - near), (-2 * far * near) / (far - near)},
		{0, 0, -1, 1}}
	};
	return (new_matrix);
}

t_matrix	create_translation_matrix(float x, float y, float z)
{
	t_matrix matrix;

	matrix = (t_matrix){ .p = {
		{1, 0, 0, x},
		{0, 1, 0, y},
		{0, 0, 1, z},
		{0, 0, 0, 1}}
	};
	return (matrix);
}

t_matrix	create_scale_matrix(float x, float y, float z)
{
	t_matrix matrix;

	matrix = (t_matrix){ .p = {
		{x == 0 ? 1 : x, 0, 0, 0},
		{0, y == 0 ? 1 : y, 0, 0},
		{0, 0, z == 0 ? 1 : z, 0},
		{0, 0, 0, 1}}
	};
	return (matrix);
}

t_matrix	new_matrix(void)
{
	t_matrix matrix;

	matrix = (t_matrix){ .p = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}}
	};
	return (matrix);
}
