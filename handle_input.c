/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 00:48:56 by nathan            #+#    #+#             */
/*   Updated: 2020/02/16 22:17:05 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firstprog.h"
#include <assert.h>

void	processInput(GLFWwindow *window, s_loop_data* data)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		data->pos.z -= 0.04;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		data->pos.z += 0.04;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		data->target.x += 0.04;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		data->target.x -= 0.04;
}
