#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

smooth out vec4 theColor;
noperspective out float outDepth;

uniform mat4 transform;
uniform vec2 camera;
uniform mat4 perspective;

void main()
{
	vec4 cam_pos  = transform * position;
	vec4 clip_pos = perspective * cam_pos;
	clip_pos.xy  += camera;

	outDepth = clip_pos.w;
	gl_Position = clip_pos;
	theColor = color;
}
