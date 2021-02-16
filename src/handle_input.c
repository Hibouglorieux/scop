/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 00:48:56 by nathan            #+#    #+#             */
/*   Updated: 2021/02/16 05:13:08 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#define MOVEMENT_PER_FRAME 0.08f

void	key_callback_with_ptr(int key, t_loop_data *ptr)
{
	static t_loop_data	*static_ptr;

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
	(void)scancode;
	(void)window;
	if (action == GLFW_PRESS)
		key_callback_with_ptr(key, NULL);
}

void	process_input(GLFWwindow *window, t_loop_data *data)
{
	int	shift;

	shift = 1;
	glfwPollEvents();
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		shift = 5;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		data->target.x -= MOVEMENT_PER_FRAME * shift;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		data->target.x += MOVEMENT_PER_FRAME * shift;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		data->target.y -= MOVEMENT_PER_FRAME * shift;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		data->target.y += MOVEMENT_PER_FRAME * shift;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		data->target.z -= MOVEMENT_PER_FRAME * shift;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		data->target.z += MOVEMENT_PER_FRAME * shift;
}
