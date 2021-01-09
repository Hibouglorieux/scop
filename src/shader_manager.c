/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 16:04:55 by nathan            #+#    #+#             */
/*   Updated: 2021/01/09 00:26:55 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firstprog.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define VERTEX_SHADER_SOURCE "shaders/basicshader.vert"
#define FRAGMENT_SHADER_SOURCE "shaders/fragment.frag"

char			*load_shader_as_string(char *str)
{
	int		fd;
	long	size;
	char	*buf;

	fd = open(str, O_RDONLY);
	assert(fd != -1);
	assert((size = lseek(fd, 0, SEEK_END)) != -1);
	lseek(fd, 0, SEEK_SET);
	buf = (char*)malloc(sizeof(char) * size + 1);
	assert(buf != NULL);
	assert(read(fd, buf, size) != -1);
	buf[size] = '\0';
	close(fd);
	return (buf);
}

GLuint	intern_load_shader(char *str, int option)
{
	GLuint	retvalue;
	char			info_log[512];
	int				success;

	retvalue = glCreateShader(option);
	glShaderSource(retvalue, 1, (const char *const *)&str, NULL);
	glCompileShader(retvalue);
	free(str);
	glGetShaderiv(retvalue, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(retvalue, 512, NULL, info_log);
		fprintf(stderr, "problem with shader compilation: %s\n", info_log);
		assert(false);
	}
	return (retvalue);
}

GLuint	compile_shader_program(GLuint vertex, GLuint frag)
{
	GLuint	shader_program;
	int				success;
	char			info_log[512];

	shader_program = glCreateProgram();
	glAttachShader(shader_program, frag);
	glAttachShader(shader_program, vertex);
	glLinkProgram(shader_program);
	glDeleteShader(vertex);
	glDeleteShader(frag);
	glGetProgramiv(shader_program, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, info_log);
		fprintf(stderr, "Problem with shader linkage: %s\n", info_log);
		return (0);
	}
	return (shader_program);
}

GLuint	load_shader(void)
{
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint shader_program;

	vertex_shader = intern_load_shader(
			load_shader_as_string(VERTEX_SHADER_SOURCE), GL_VERTEX_SHADER);
	fragment_shader = intern_load_shader(
			load_shader_as_string(FRAGMENT_SHADER_SOURCE), GL_FRAGMENT_SHADER);
	shader_program = compile_shader_program(vertex_shader, fragment_shader);
	assert(shader_program);
	return (shader_program);
}

GLuint	init_shader(GLuint shader_program)
{
	glUseProgram(shader_program);
	return (shader_program);
}
