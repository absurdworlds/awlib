#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

smooth out vec4 theColor;
noperspective out float outDepth;

uniform mat4 camera;
uniform mat4 perspective;
uniform mat4 transform;

uniform float time;
uniform mat4  rot;

void main()
{
	//vec4 transform1 = rot * fwd;
	vec4 world_pos = transform   * position;

	mat4 cpos = mat4(1.0);
	cpos[3]  += time * (vec4(0,0,1,0) * rot);

	vec4 cam_pos   = cpos * (rot  * world_pos);
	vec4 clip_pos  = perspective * cam_pos;

	outDepth = clip_pos.w;
	gl_Position = clip_pos;
	theColor = color;
}`
