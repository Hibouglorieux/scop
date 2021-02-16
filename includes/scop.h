/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 20:13:00 by nathan            #+#    #+#             */
/*   Updated: 2021/02/16 05:05:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <GL/glew.h>
# include <GL/gl.h>
# include <glfw3.h>
# include <stdbool.h>
# include "libft.h"
# define SCREEN_WIDTH 800.0f
# define SCREEN_HEIGHT 600.0f
# define MAX_POINTS_PER_FACE 1024

typedef struct	s_parsed_data
{
	float	*data;
	int		nb_points;
	int		nb_triangles;
}				t_parsed_data;

typedef struct	s_internal_tmp_parsing
{
	int			*points_index;
	int			nb_triangles;
	int			nb_unique_points;
	float		*raw_points;
}				t_internal_tmp_parsing;

typedef struct	s_vector
{
	float x;
	float y;
	float z;
	float w;
}				t_vector;

typedef	struct	s_matrix
{
	float	p[4][4];
}				t_matrix;

typedef struct	s_matrixes
{
	t_matrix view;
	t_matrix projection;
	t_matrix model;
}				t_matrixes;

typedef struct	s_locations
{
	GLuint		model_matrix;
	GLuint		view_matrix;
	GLuint		texture_factor;
}				t_locations;

typedef struct	s_loop_data
{
	GLuint			vao;
	GLuint			vbo;
	GLuint			texture;
	GLuint			shader_program;
	t_matrixes		matrixes;
	t_vector		pos;
	t_vector		target;
	int				how_to_render;
	t_locations		uniforms;
	t_parsed_data	parse_data;
}				t_loop_data;

/*
** handle_input.c
*/
void			key_callback_with_ptr(int key, t_loop_data *ptr);
void			key_callback(GLFWwindow *window, int key, int scancode,
		int action);
void			process_input(GLFWwindow *window, t_loop_data *alpha);

/*
** shader_manager.c
*/
GLuint			load_shader();
GLuint			init_shader(unsigned int shader_program);

/*
** loop.c
*/
void			loop(GLFWwindow *window, t_loop_data *data);

/*
** initialize.c
*/
t_matrix		ini_camera(t_vector pos, t_vector dir);
int				initialize_libs_and_buffers(GLFWwindow **window);
void			initialize_buffers(t_loop_data *data);
void			initialize_data(t_loop_data *data, char **file_path);

/*
** main.c
*/
GLuint			load_texture(char *path, bool has_alpha);
int				glfw_init(GLFWwindow **window);
int				glew_init(void);

/*
** obj_parser2.c
*/

int				scop_sscanf(const char *str, float f[3]);
t_vector		center_model_mat(t_parsed_data *data);
void			copy_triangles(int end_index, int *dest, int *src);
void			load_triangles(char *buf, int index[4], int *index_found);

/*
** obj_parser.c
*/
t_parsed_data	parse_file(char *path_to_file);

/*
** math_util.c
*/
float			to_rad(float f);
t_vector		add_vector(t_vector a, t_vector b);
t_vector		sub_vector(t_vector a, t_vector b);
t_vector		cross_product(t_vector a, t_vector b);
t_vector		normalize(t_vector a);

/*
** matrix.c
*/
t_matrix		create_proj_matrix(float fov, float aspect, float near,
		float far);
t_matrix		create_scale_matrix(float x, float y, float z);
t_matrix		create_translation_matrix(float x, float y, float z);
t_matrix		new_matrix(void);

/*
** matrix_operation.c
*/
GLfloat			*export_matrix(t_matrix *matrix);
t_matrix		mult_matrix(t_matrix a, t_matrix b);
t_matrix		create_x_rot_matrix(float angle);
t_matrix		create_y_rot_matrix(float angle);
t_matrix		create_z_rot_matrix(float angle);

#endif
