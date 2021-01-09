#ifndef __FIRSTPROG__
# define __FIRSTPROG__

#include <GL/glew.h>
#include <GL/gl.h>
//#include <GL/glext.h>
#include <glfw3.h>
#include <math.h>
#include <stdbool.h>
#include "libft.h"

#define SCREEN_WIDTH 800.0f
#define SCREEN_HEIGHT 600.0f
#define FLOAT_BUFFER_OFFSET(i) (void*)(NULL + sizeof(float) * i)

typedef struct parsed_data
{
	float*	data; // nb_points * (3(xyz) + 2(texturecoords))
	int		nb_points;
	int		nb_triangles;
}				s_parsed_data;

typedef struct internal_tmp_parsing
{
	int*		points_index;
	int			nb_triangles;
	int			nb_unique_points;
	float*		raw_points;
}				s_internal_tmp_parsing;

typedef struct	vector
{
	float x;
	float y;
	float z;
	float w;
}				s_vector;

typedef struct	matrix
{
	float	p[4][4];
}				s_matrix;

typedef struct	matrixes
{
	s_matrix view;
	s_matrix projection;
	s_matrix model;
}				s_matrixes;

typedef struct loop_data
{
	GLuint			vao;
	GLuint			vbo;
	GLuint			texture_buffer;
	GLuint 			texture;
	GLuint 			shader_program;
	s_matrixes		matrixes;
	s_vector		pos;
	s_vector		target;
	float			pitch;
	float			yaw;
	int				how_to_render;
	s_parsed_data		parse_data;
}				s_loop_data;

/*
 * handle_input.c
 */
void				key_callback_with_ptr(int key, s_loop_data* ptr);
void				key_callback(GLFWwindow* window, int key, int scancode, int action);
void				process_input(GLFWwindow *window, s_loop_data* alpha);

/*
 * shader_manager.c
 */
GLuint				load_shader();
GLuint 				init_shader(unsigned int shader_program);

/*
 * loop.c
 */
void				loop(GLFWwindow *window, s_loop_data *data);

/*
 * initialize.c
 */
s_matrixes			initialize_matrixes(GLuint shader_program);
s_matrix			ini_camera(s_vector pos, s_vector dir);
int					initialize_libs_and_buffers(GLFWwindow **window);
void				initialize_buffers(s_loop_data *data);
void				initialize_data(s_loop_data *data, char **file_path);

/*
 * main.c
 */
GLuint				load_texture(char *path, bool has_alpha);
int					glfw_init(GLFWwindow **window);
int					glew_init(void);


GLfloat*			export_matrix(s_matrix* matrix);
s_matrix			mult_matrix(s_matrix a, s_matrix b);
s_matrix			create_x_rot_matrix(float angle);
s_matrix			create_y_rot_matrix(float angle);
s_matrix			create_z_rot_matrix(float angle);
s_matrix			create_scale_matrix(float x, float y, float z);
s_matrix			new_matrix();
s_matrix			create_proj_matrix(float fov, float aspect, float near, float far);
s_matrix			create_translation_matrix(float x, float y, float z);
void				print_matrix(s_matrix a);
float				to_rad(float f);
s_vector			add_vector(s_vector a, s_vector b);
s_vector			sub_vector(s_vector a, s_vector b);
s_vector			cross_product(s_vector a, s_vector b);
s_vector			normalize(s_vector a);
void				print_vector(s_vector a);

s_parsed_data		parse_file(char* path_to_file);

# endif
