#version 450 core

in vec2 			texCoord;
in vec3 			color;

uniform float 		textureFactor;
uniform sampler2D	texture0;

out vec4			FragColor;

void main()
{
	vec4 texture_color_factor = vec4(textureFactor, textureFactor,
			textureFactor, 1.0f);
	FragColor = texture(texture0, texCoord);
	float f = gl_PrimitiveID % 6 * 0.1f + 0.2f;
	FragColor = vec4(f, f, f, 1.0) * (1.0f - textureFactor) +
		FragColor * textureFactor;
};
