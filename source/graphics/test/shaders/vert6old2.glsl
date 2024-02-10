#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

smooth out vec4 theColor;
smooth out vec3 theNormal;

layout(std140) uniform common_data {
	uniform mat4 perspective;
	uniform vec4 light_intensity;
	uniform vec3 light_dir;
};

uniform mat4 transform;
uniform mat4 camtrafo;
uniform mat4 world;

void main()
{
	//vec4 world_pos = transform   * position;
	vec4 cam_pos   = transform   * position;
	vec4 clip_pos  = perspective * cam_pos;

	//vec3 normal_world = mat3(transform) * normal;
	vec3 normal_cam   = mat3(transform)    * normal;

	mat3 wmat = mat3(world);
	//vec3 light_world = mat3(transform) * light_dir;
	vec3 light_cam   = vec3(0,0,0) - wmat*vec3(cam_pos);
	light_cam = mat3(camtrafo)*light_cam;

	normal_cam = normalize(normal_cam);
	float cosa = dot(normal_cam, normalize(light_cam));
	cosa = clamp(cosa, 0.1, 1);

	gl_Position = clip_pos;
	theColor = light_intensity * vec4(1,1,1,1) * cosa;// + vec4(0.2,0.2,0.2,1);
	theNormal = normal;
}
