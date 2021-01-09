/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 00:48:56 by nathan            #+#    #+#             */
/*   Updated: 2021/01/09 02:23:38 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firstprog.h"
#include <assert.h>

#define MOVEMENT_PER_FRAME 0.04f

void	key_callback_with_ptr(int key, s_loop_data *ptr)
{
	static s_loop_data	*static_ptr;

	if (ptr != NULL)
	{
		static_ptr = ptr;
		return ;
	}
	if (key == GLFW_KEY_R)
		static_ptr->how_to_render = !(static_ptr->how_to_render);
}

void	key_callback(GLFWwindow *window, int key, int scancode,
		int action)
{
	//(void)mods;
	(void)scancode;
	(void)window;
	if (action == GLFW_PRESS)
		key_callback_with_ptr(key, NULL);
}

void	process_input(GLFWwindow *window, s_loop_data *data)
{
	glfwPollEvents();
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		data->pos.z -= MOVEMENT_PER_FRAME;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		data->pos.z += MOVEMENT_PER_FRAME;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		data->pos.x += MOVEMENT_PER_FRAME;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		data->pos.x -= MOVEMENT_PER_FRAME;
}
