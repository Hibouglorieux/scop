/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:43:38 by nathan            #+#    #+#             */
/*   Updated: 2021/02/15 23:59:19 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

float		to_rad(float f)
{
	return (f * M_PI / 180);
}

t_vector	sub_vector(t_vector a, t_vector b)
{
	t_vector new_vector;

	new_vector = (t_vector){
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
		a.w - b.w
	};
	return (new_vector);
}

t_vector	add_vector(t_vector a, t_vector b)
{
	t_vector new_vector;

	new_vector = (t_vector){
		a.x + b.x,
		a.y + b.y,
		a.z + b.z,
		a.w + b.w
	};
	return (new_vector);
}

t_vector	cross_product(t_vector a, t_vector b)
{
	t_vector new_vector;

	new_vector.x = a.y * b.z - a.z * b.y;
	new_vector.y = a.z * b.x - a.x * b.z;
	new_vector.z = a.x * b.y - a.y * b.x;
	new_vector.w = 1.0;
	return (new_vector);
}

t_vector	normalize(t_vector a)
{
	t_vector	normalized_vector;
	float		length;

	length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	normalized_vector.x = a.x / length;
	normalized_vector.y = a.y / length;
	normalized_vector.z = a.z / length;
	return (normalized_vector);
}
