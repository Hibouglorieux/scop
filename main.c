
#include <stdlib.h>
#include <stdio.h>
#include "firstprog.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Include GLFW


int	glfw_init( GLFWwindow** window )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // antilia4ing x4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // openGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); // "
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // no support from old openGL
	// Open a window and create its OpenGL context
	*window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Tutorial 01", NULL, NULL);
	if( *window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(*window);
	return (0);
}

int glew_init( void )
{
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	return (0);
}

unsigned int load_texture(char* path, bool has_alpha)
{
	unsigned int	id;
	int				height, width, nrChannel;
	unsigned char	*data;

	data = stbi_load(path, &width, &height, &nrChannel, 0);

	assert(data && "couldn't load image correctly with stbi_load");
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (!has_alpha)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	return (id);
}

s_matrix	ini_camera(s_vector pos, s_vector target)
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

int main( void )
{
	GLFWwindow* window;

	if (glfw_init(&window))
		return (-1);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (glew_init())
		return (-1);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.2f, 0.0f); // background color
	glEnable(GL_DEPTH_TEST); // z_buffer
	/*
	   const GLfloat g_vertex_buf_data[] = {
	   -0.5, 0.5, 0.0,			0.6, 0.6, 0.0, 		0, 1.0, 
	   0.5, 0.5, 0.0,			0.6, 0.6, 0.0,		1.0, 1.0, 
	   0.5, -0.5, 0.0,			0.6, 0.6, 0.0,		1.0, 0.0, 
	   -0.5, -0.5, 0.0,		0.6, 0.6, 0.0,		0.0, 0.0,
	   };
	   */
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	const GLuint elem_array_buffer[] ={
		0, 1, 2,
		0, 3, 2
	};

	//init vertex
	GLuint VAO, vertexbuffer, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elem_array_buffer), elem_array_buffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0); // free memory
	glBindVertexArray(0); // free

	unsigned int shaderProgram = load_shader();
	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

	unsigned int container = load_texture("images/container.jpg", false);
	stbi_set_flip_vertically_on_load(true);
	unsigned int face = load_texture("images/happy.png", true);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, container);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, face);

	s_matrix model = create_x_rot_matrix(to_rad(-55));
	s_matrix view = ini_camera((s_vector){0.0f, 0.0f, 3.0f, 1.0f}, (s_vector){0.0f, 0.0f, 0.0f, 1.0f});
	s_matrix proj = create_proj_matrix(45, SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_TRUE, export_matrix(&view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_TRUE, export_matrix(&proj));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_TRUE, export_matrix(&model));
	s_matrix good_matrix = view;
	s_loop_data data = {
		.vao = VAO,
		.textureID = {container, face},
		.shaderProgram = shaderProgram,
		.matrix = good_matrix,
		.pos = (s_vector){0.0f, 0.0f, 3.0f, 1.0f},
		.target = (s_vector){0.0f, 0.0f, 0.0f, 1.0f},
		.pitch = 0.0f, 0.0f, 0.0f,
		.parse_data = ft_parse_file("resources/42.obj")
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.parse_data->nb_points, data.parse_data->points_data, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * data.parse_data->nb_of_triangles, data.parse_data->triangles_data, GL_STATIC_DRAW);
	printf("ok\n");
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	loop(window, data);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return (0);
}
