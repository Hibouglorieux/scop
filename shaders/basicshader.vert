#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 textureCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec3 color;
out vec2 texCoord;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	color = aPos;
	texCoord = textureCoord;
};
