/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaderManager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 16:04:55 by nathan            #+#    #+#             */
/*   Updated: 2020/02/09 17:08:20 by nathan           ###   ########.fr       */
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

char* load_shader_as_string(char *str)
{
	int fd;
	long size;
	char* buf;

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

unsigned int intern_load_shader(char *str, int option)
{
	unsigned int retvalue;
	char infoLog[512];
	int success;

	retvalue = glCreateShader(option);
	glShaderSource(retvalue, 1, (const char * const *)&str, NULL);
	glCompileShader(retvalue);
	free(str);
	glGetShaderiv(retvalue, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(retvalue, 512, NULL, infoLog);
		printf("problem with shader compilation: %s\n", infoLog);
		assert(false);
	}
	return (retvalue);
}

unsigned int	compile_shader_program(unsigned int vertex, unsigned int frag)
{
	unsigned int	shaderProgram;
	int				success;
	char			infoLog[512];

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, frag);
	glAttachShader(shaderProgram, vertex);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertex);
	glDeleteShader(frag);
	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Problem with shader linkage: %s\n", infoLog);
		return (0);
	}
	return (shaderProgram);
}

unsigned int	load_shader()
{	
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	vertexShader = intern_load_shader(load_shader_as_string(VERTEX_SHADER_SOURCE), GL_VERTEX_SHADER);
	fragmentShader = intern_load_shader(load_shader_as_string(FRAGMENT_SHADER_SOURCE), GL_FRAGMENT_SHADER);
	shaderProgram = compile_shader_program(vertexShader, fragmentShader);
	assert(shaderProgram);
	return (shaderProgram);
}
