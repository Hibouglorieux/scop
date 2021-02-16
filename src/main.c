/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 13:08:44 by nathan            #+#    #+#             */
/*   Updated: 2021/02/15 23:59:05 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define DEFAULT_FILE "resources/42.obj"

int		glfw_init(GLFWwindow **window)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return (-1);
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	*window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Scop", NULL,
			NULL);
	if (*window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window");
		getchar();
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(*window);
	return (0);
}

int		glew_init(void)
{
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return (-1);
	}
	return (0);
}

GLuint	load_texture(char *path, bool has_alpha)
{
	unsigned int	id;
	int				height;
	int				width;
	int				nr_channel;
	unsigned char	*data;

	data = stbi_load(path, &width, &height, &nr_channel, 0);
	assert(data && "couldn't load image correctly with stbi_load");
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if (!has_alpha)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
				GL_UNSIGNED_BYTE, data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	return (id);
}

void	release_data(t_loop_data *data)
{
	free(data->parse_data.data);
	glDeleteBuffers(1, &data->vbo);
	glDeleteVertexArrays(1, &data->vao);
	glDeleteTextures(1, &data->texture);
	glDeleteProgram(data->shader_program);
	glfwTerminate();
}

int		main(int argc, char **argv)
{
	GLFWwindow	*window;
	char		*file_path;
	t_loop_data	data;

	if (initialize_libs_and_buffers(&window))
		return (-1);
	if (argc > 1)
		file_path = argv[1];
	else
		file_path = DEFAULT_FILE;
	initialize_buffers(&data);
	initialize_data(&data, &file_path);
	loop(window, &data);
	release_data(&data);
	return (0);
}
