#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoord;
layout (location = 5) in float material_id;

out vec2 f_texCoord;

smooth out vec4 lightness;
flat out float matid;

layout(std140) uniform common_data {
	uniform mat4 perspective;
	uniform vec4 light_intensity;
	uniform vec3 light_dir;
};

uniform mat4 transform;

void main()
{
	//vec4 world_pos = transform   * position;
	vec4 cam_pos   = transform   * position;
	vec4 clip_pos  = perspective * cam_pos;

	//vec3 normal_world = mat3(transform) * normal;
	vec3 normal_cam   = mat3(transform)    * normal;

	//vec3 light_world = mat3(transform) * light_dir;
	vec3 light_cam   = mat3(transform)    * light_dir;

	normal_cam = normalize(normal_cam);
	float cosa = dot(normal_cam, light_cam);
	cosa = clamp(cosa, 0, 1);

	gl_Position = clip_pos;
	lightness = light_intensity * cosa;
	f_texCoord = vec2(texCoord);
	matid = material_id;
}
