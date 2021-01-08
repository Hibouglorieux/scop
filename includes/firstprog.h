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

typedef struct parsing
{
	int		nb_points;
	float*	points_data;	
	int		nb_of_triangles;
	GLuint*	triangles_data;
	int		nb_of_faces;
	int*	triangle_per_face;
	float*	texture_data;
}				s_parsing;

typedef struct exploitable_parsed_data
{
	float*	data; // nb_points * (3(xyz) + 2(texturecoords))
	int		nb_points;
	int		nb_triangles;
}				s_exploitable_parsed_data;

typedef struct internal_tmp_parsing
{
	int*		points_index;
	int			nb_triangles;
	int			nb_unique_points;
	float*		raw_points;
}				s_internal_tmp_parsing;

typedef struct	vec2
{
	float x;
	float y;
}				s_vec2;
		
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

typedef struct loop_data
{
	unsigned int	vao;
	unsigned int	textureID[100];
	unsigned int	shaderProgram;
	s_matrix		matrix;
	s_vector		pos;
	s_vector		target;
	float			pitch;
	float			yaw;
	float			deltaTime;
	s_exploitable_parsed_data		parse_data;
}				s_loop_data;

void				processInput(GLFWwindow *window, s_loop_data* alpha);
unsigned int		load_shader();
void				loop(GLFWwindow *window, s_loop_data* data);
s_matrix			ini_camera(s_vector pos, s_vector target);
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

s_parsing			ft_parse_file(char* path_to_file);
s_exploitable_parsed_data	new_ft_parse_file(char* path_to_file);

# endif
