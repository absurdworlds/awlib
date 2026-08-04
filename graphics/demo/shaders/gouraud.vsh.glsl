#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

smooth out vec4 theColor;
noperspective out float outDepth;

layout(std140) uniform common_data {
	uniform mat4 perspective;
	uniform vec4 light_intensity;
	uniform vec3 light_dir;
};

vec4 calc_light(in vec3 normal_cam, in vec3 light_cam, in vec4 light_intensity);

uniform mat4 transform;
void main()
{
	//vec4 world_pos = transform   * position;
	vec4 cam_pos   = transform   * position;
	vec4 clip_pos  = perspective * cam_pos;

	//vec3 normal_world = mat3(transform) * normal;
	vec3 normal_cam   = mat3(transform)    * normal;
	normal_cam = normalize(normal_cam);

	//vec3 light_world = mat3(transform) * light_dir;
	vec3 light_cam   = mat3(transform)    * light_dir;

	float cosa = dot(normal_cam, light_cam);
	cosa = clamp(cosa, 0, 1);

	outDepth = clip_pos.w;
	gl_Position = clip_pos;
	theColor = calc_light(normal_cam, light_cam, light_intensity) * vec4(0.5,0.5,0.5,1);// + vec4(0.2,0.2,0.2,1);
}
