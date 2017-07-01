#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

smooth out vec4 theColor;
noperspective out float outDepth;

uniform mat4 camera;
uniform mat4 perspective;
uniform mat4 transform;

void main()
{
	vec4 world_pos = transform   * position;
	vec4 cam_pos   = camera      * world_pos;
	vec4 clip_pos  = perspective * cam_pos;

	outDepth = clip_pos.w;
	gl_Position = clip_pos;
	theColor = color;
}
