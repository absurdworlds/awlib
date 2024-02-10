#version 330

layout (location = 0) in vec4 position;

smooth out vec4 theColor;

layout(std140) uniform common_data {
	uniform mat4 perspective;
	uniform vec4 light_intensity;
	uniform vec3 light_dir;
};

uniform mat4 transform;
uniform mat4 camtrafo;
uniform int matid;

void main()
{
	//vec4 world_pos = transform   * position;
	vec4 clip_pos  = perspective * camtrafo *  position;
	gl_Position = clip_pos;
	theColor = position;
}
