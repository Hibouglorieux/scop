#version 450 core
in vec3 color;
in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D	texture1;
uniform sampler2D	texture2;
uniform float		alpha;

void main()
{
	FragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(-1 * texCoord.x,texCoord.y)), alpha);
//	FragColor = vec4(color.x, color.y, color.z, 1.0f);
	
};
