/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:09:10 by nathan            #+#    #+#             */
/*   Updated: 2021/01/09 02:24:50 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firstprog.h"
#include <stdio.h>

#define FPS 60.f
#define REFRESHING_RATE 1.f / FPS
#define SEC_TO_MICROSEC 1000000
#define TO_COLOR 0
#define TO_TEXTURE 1

void	update_matrixes(s_loop_data *data)
{
	GLuint matrixLoc = glGetUniformLocation(data->shader_program, "model");
	GLuint viewMatrixLoc = glGetUniformLocation(data->shader_program, "view");

	data->matrixes.view = ini_camera(data->pos, data->target);
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_TRUE,
			export_matrix(&data->matrixes.view));
	data->matrixes.model = mult_matrix(new_matrix(),
			create_y_rot_matrix(to_rad(30) * glfwGetTime()));
	glUniformMatrix4fv(matrixLoc, 1, GL_TRUE,
			export_matrix(&data->matrixes.model));
}

void	loop(GLFWwindow* window, s_loop_data *data)
{
	double current_time = 0.0f;
	GLuint textureFactorLoc = glGetUniformLocation(data->shader_program, "textureFactor");
	GLfloat textureFactor = 0.0f;
	key_callback_with_ptr(0, data);
	glfwSetKeyCallback(window, (void*)key_callback);
	while(glfwWindowShouldClose(window) == 0)
	{	
		current_time = glfwGetTime();
		process_input(window, data);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		update_matrixes(data);
		glUniform1f(textureFactorLoc, textureFactor);
		glDrawArrays(GL_TRIANGLES, 0, data->parse_data.nb_triangles * 3);
		glFinish();

		glfwSwapBuffers(window);

		if (glfwGetTime() - current_time < REFRESHING_RATE)
		{
			usleep((REFRESHING_RATE - (glfwGetTime() - current_time)) * SEC_TO_MICROSEC);
		}
		if (data->how_to_render == TO_TEXTURE && textureFactor < 1.0f)
			textureFactor += 0.01f;
		if (data->how_to_render == TO_COLOR && textureFactor > 0.0f)
			textureFactor -= 0.01f;
	} // Check if the ESC key was pressed or the window was closed
}
