#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoord;

smooth out vec2 f_texCoord;

layout(std140) uniform common_data {
	uniform mat4 perspective;
	uniform vec4 light_intensity;
	uniform vec3 light_dir;
};

uniform mat4 camtrafo;

void main()
{
	mat4 trafo = camtrafo;
	trafo[3] = vec4(0,0,0,1);

	f_texCoord = texCoord;
	gl_Position = perspective * trafo * position;
}
