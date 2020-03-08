/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:09:10 by nathan            #+#    #+#             */
/*   Updated: 2020/03/08 17:15:38 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firstprog.h"
#include <stdio.h>

void	loop(GLFWwindow* window, s_loop_data* data)
{
	float oldTime = 0.0f;
	float alpha = 0.2;
	GLuint matrixLoc = glGetUniformLocation(data->shaderProgram, "model");
	float alphaLoc = glGetUniformLocation(data->shaderProgram, "alpha");
	GLuint viewMatrixLoc = glGetUniformLocation(data->shaderProgram, "view");
	while( glfwWindowShouldClose(window) == 0 )
	{
		
		data->deltaTime = glfwGetTime() - oldTime;
		oldTime = data->deltaTime;
		//input 
		processInput(window, data);
		glUniform1f(alphaLoc, alpha);
		//render
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		data->matrix = ini_camera(data->pos, data->target);
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_TRUE, export_matrix(&data->matrix));

		//glBindVertexArray(data->vao);
		s_matrix matrix = new_matrix();
		//matrix = mult_matrix(matrix, mult_matrix(create_x_rot_matrix(to_rad(20) * glfwGetTime()), create_y_rot_matrix(to_rad(to_rad(1)) * glfwGetTime())));
		matrix = mult_matrix(matrix, create_y_rot_matrix(to_rad(30) * glfwGetTime()));
		glUniformMatrix4fv(matrixLoc, 1, GL_TRUE, export_matrix(&matrix));
		glDrawElements(GL_TRIANGLES, data->parse_data.nb_of_triangles, GL_UNSIGNED_INT, (void*)0);//TODO problem here

		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
}
