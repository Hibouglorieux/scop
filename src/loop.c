/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:09:10 by nathan            #+#    #+#             */
/*   Updated: 2021/01/13 10:56:15 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdio.h>

#define REFRESHING_RATE 0.0166666667f
#define SEC_TO_MICROSEC 1000000
#define TO_COLOR 0
#define TO_TEXTURE 1

void	update_matrixes(t_loop_data *data)
{
	data->matrixes.view = ini_camera(data->pos, data->target);
	glUniformMatrix4fv(data->uniforms.view_matrix, 1, GL_TRUE,
			export_matrix(&data->matrixes.view));
	data->matrixes.model = mult_matrix(new_matrix(),
			create_y_rot_matrix(to_rad(30) * glfwGetTime()));
	glUniformMatrix4fv(data->uniforms.model_matrix, 1, GL_TRUE,
			export_matrix(&data->matrixes.model));
}

void	update_texture_factor(t_loop_data *data)
{
	static GLfloat texture_factor = 0.0f;

	if (data->how_to_render == TO_TEXTURE && texture_factor < 1.0f)
		texture_factor += 0.01f;
	if (data->how_to_render == TO_COLOR && texture_factor > 0.0f)
		texture_factor -= 0.01f;
	if (texture_factor > 1.0f)
		texture_factor = 1.0f;
	if (texture_factor < 0.0f)
		texture_factor = 0.0f;
	glUniform1f(data->uniforms.texture_factor, texture_factor);
}

void	loop(GLFWwindow *window, t_loop_data *data)
{
	double current_time;

	current_time = 0.0f;
	key_callback_with_ptr(0, data);
	glfwSetKeyCallback(window, (void*)key_callback);
	while (glfwWindowShouldClose(window) == 0)
	{
		current_time = glfwGetTime();
		process_input(window, data);
		update_texture_factor(data);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update_matrixes(data);
		glDrawArrays(GL_TRIANGLES, 0, data->parse_data.nb_triangles * 3);
		glFinish();
		glfwSwapBuffers(window);
		if (glfwGetTime() - current_time < REFRESHING_RATE)
		{
			usleep((REFRESHING_RATE - (glfwGetTime() - current_time))
					* SEC_TO_MICROSEC);
		}
	}
}
