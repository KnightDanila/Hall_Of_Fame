#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

void main()
{
	float t = 1.5f + cos(time) / 1.5;
	gl_Position = projection * view * model * vec4(aPos, 1 / t);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
