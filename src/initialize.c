/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:12:24 by nathan            #+#    #+#             */
/*   Updated: 2021/02/16 05:12:54 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
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

t_matrix		ini_camera(t_vector pos, t_vector target)
{
	t_vector dir;
	t_vector right;
	t_vector up;

	dir = normalize(sub_vector(pos, target));
	right = normalize(cross_product((t_vector){0.0f, 1.0f, 0.0f, 1.0f},
				dir));
	up = cross_product(dir, right);
	return (t_matrix){ .p = {
		{ right.x, right.y, right.z, -pos.x },
		{ up.x, up.y, up.z, -pos.y },
		{ dir.x, dir.y, dir.z, -pos.z },
		{ 0, 0, 0, 1 }}
	};
}

t_matrixes		initialize_matrixes(GLuint shader_program, t_vector target)
{
	t_matrixes matrixes;

	matrixes.model = create_translation_matrix(target.x, target.y, target.z);
	matrixes.view = ini_camera((t_vector){0.0f, 0.0f, 20.0f, 1.0f},
			(t_vector){0.0f, 0.0f, 0.0f, 1.0f});
	matrixes.projection = create_proj_matrix(45, SCREEN_WIDTH / SCREEN_HEIGHT,
			0.2f, 1000.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "view"), 1,
			GL_TRUE, export_matrix(&matrixes.view));
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1,
			GL_TRUE, export_matrix(&matrixes.projection));
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1,
			GL_TRUE, export_matrix(&matrixes.model));
	return (matrixes);
}

void			initialize_buffers(t_loop_data *data)
{
	data->shader_program = init_shader(load_shader());
	glGenVertexArrays(1, &data->vao);
	glGenBuffers(1, &data->vbo);
	glBindVertexArray(data->vao);
	glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
	stbi_set_flip_vertically_on_load(true);
	data->texture = load_texture("images/cat.png", true);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data->texture);
	glUniform1i(glGetUniformLocation(data->shader_program, "texture0"), 0);
}

void			initialize_data(t_loop_data *data, char **file_path)
{
	data->parse_data = parse_file(*file_path);
	data->pos = (t_vector){0.0f, 0.0f, 3.0f, 1.0f};
	data->target = center_model_mat(&data->parse_data);
	data->matrixes = initialize_matrixes(data->shader_program, data->target);
	data->how_to_render = 0;
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data->parse_data.nb_points *
			(3 + 2), data->parse_data.data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * (3 + 2),
			(void*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * (3 + 2),
			NULL + sizeof(float) * 3);
	data->uniforms.model_matrix = glGetUniformLocation(data->shader_program,
			"model");
	data->uniforms.view_matrix = glGetUniformLocation(data->shader_program,
			"view");
	data->uniforms.texture_factor = glGetUniformLocation(data->shader_program,
			"textureFactor");
}
