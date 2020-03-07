/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:09:10 by nathan            #+#    #+#             */
/*   Updated: 2020/03/07 22:26:27 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firstprog.h"

void	loop(GLFWwindow* window, s_loop_data data)
{
	float cubePos[11][3] = {
	  { 0.0f,  0.0f,  0.0f}, 
	  { 2.0f,  5.0f, -15.0f}, 
	  {-1.5f, -2.2f, -2.5f},  
	  {-3.8f, -2.0f, -12.3f},  
	  { 2.4f, -0.4f, -3.5f},  
	  {-1.7f,  3.0f, -7.5f},  
	  { 1.3f, -2.0f, -2.5f},  
	  { 1.5f,  2.0f, -2.5f}, 
	  { 1.5f,  0.2f, -1.5f}, 
	  {-1.3f,  1.0f, -1.5f},
	  {-2.0f,  -0.2f, 0.5f}  
	};
	float oldTime = 0.0f;
	float alpha = 0.2;
	GLuint matrixLoc = glGetUniformLocation(data.shaderProgram, "model");
	float alphaLoc = glGetUniformLocation(data.shaderProgram, "alpha");
	GLuint viewMatrixLoc = glGetUniformLocation(data.shaderProgram, "view");
	while( glfwWindowShouldClose(window) == 0 )
	{
		
		data.deltaTime = glfwGetTime() - oldTime;
		oldTime = data.deltaTime;
		//input 
		processInput(window, &data);
		glUniform1f(alphaLoc, alpha);
		//render
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		data.matrix = ini_camera(data.pos, data.target);
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_TRUE, export_matrix(&data.matrix));

		glBindVertexArray(data.vao);
		for (int i = 0; i < 11; i++)
		{
			s_matrix matrix = create_translation_matrix(cubePos[i][0], cubePos[i][1], cubePos[i][2]);
			float ang = (i + 1) * 20.0f;
			matrix = mult_matrix(matrix, mult_matrix(create_x_rot_matrix(to_rad(ang * 0.5) * glfwGetTime()), create_y_rot_matrix(to_rad(ang) * glfwGetTime())));
		glUniformMatrix4fv(matrixLoc, 1, GL_TRUE, export_matrix(&matrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
}
