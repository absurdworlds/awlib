#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

smooth out vec4 theColor;
noperspective out float outDepth;

uniform vec3 light_dir;
uniform vec4 light_intensity;

uniform mat4 camera;
uniform mat4 perspective;
uniform mat4 transform;

void main()
{
	vec4 world_pos = transform   * position;
	vec4 cam_pos   = camera      * world_pos;
	vec4 clip_pos  = perspective * cam_pos;

	vec3 normal_world = mat3(transform) * normal;
	vec3 normal_cam   = mat3(camera)    * normal_world;

	vec3 light_world = mat3(transform) * light_dir;
	vec3 light_cam   = mat3(camera)    * light_world;

	normal_cam = normalize(normal_cam);
	float cosa = dot(normal_cam, light_cam);
	cosa = clamp(cosa, 0, 1);

	outDepth = clip_pos.w;
	gl_Position = clip_pos;
	theColor = light_intensity * vec4(0.5,0.5,0.5,1) * cosa;// + vec4(0.2,0.2,0.2,1);
}
