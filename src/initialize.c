/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:12:24 by nathan            #+#    #+#             */
/*   Updated: 2021/01/09 00:02:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firstprog.h"
#include "stb_image.h"

int				initialize_libs_and_buffers(GLFWwindow **window)
{
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (glfw_init(window))
		return (-1);
	if (glew_init())
		return (-1);
	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	return (0);
}

s_matrix		ini_camera(s_vector pos, s_vector target)
{
	s_vector dir;
	s_vector right;
	s_vector up;

	dir = normalize(sub_vector(pos, target));
	right = normalize(cross_product((s_vector){0.0f, 1.0f, 0.0f, 1.0f}, dir));
	up = cross_product(dir, right);
	return (s_matrix){ .p = {
		{ right.x, right.y, right.z, -pos.x },
		{ up.x, up.y, up.z, -pos.y },
		{ dir.x, dir.y, dir.z, -pos.z },
		{ 0, 0, 0, 1 }}
	};
}

s_matrixes		initialize_matrixes(GLuint shader_program)
{
	s_matrixes matrixes;

	matrixes.model = create_x_rot_matrix(to_rad(-55));
	matrixes.view = ini_camera((s_vector){0.0f, 0.0f, 3.0f, 1.0f},
			(s_vector){0.0f, 0.0f, 0.0f, 1.0f});
	matrixes.projection = create_proj_matrix(45, SCREEN_WIDTH / SCREEN_HEIGHT,
			0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "view"), 1,
			GL_TRUE, export_matrix(&matrixes.view));
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1,
			GL_TRUE, export_matrix(&matrixes.projection));
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1,
			GL_TRUE, export_matrix(&matrixes.model));
	return (matrixes);
}

void			initialize_buffers(s_loop_data *data)
{
	data->shader_program = init_shader(load_shader());
	glGenVertexArrays(1, &data->vao);
	glGenBuffers(1, &data->vbo);
	glBindVertexArray(data->vao);
	glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
	stbi_set_flip_vertically_on_load(true);
	data->texture = load_texture("images/happy.png", true);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data->texture);
	glUniform1i(glGetUniformLocation(data->shader_program, "texture0"), 0);
}

void			initialize_data(s_loop_data *data, char **file_path)
{
	data->parse_data = parse_file(*file_path);
	free(*file_path);
	*file_path = NULL;
	data->matrixes = initialize_matrixes(data->shader_program);
	data->pos = (s_vector){0.0f, 0.0f, 3.0f, 1.0f};
	data->target = (s_vector){0.0f, 0.0f, 0.0f, 1.0f};
	data->pitch = 0.0f;
	data->yaw = 0.0f;
	data->how_to_render = 0;
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data->parse_data.nb_points *
			(3 + 2), data->parse_data.data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * (3 + 2),
			(void*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * (3 + 2),
			FLOAT_BUFFER_OFFSET(3));
}
