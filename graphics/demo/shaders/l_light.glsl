#version 330 core

vec4 calc_light(in vec3 normal_cam, in vec3 light_cam, in vec4 light_intensity)
{
	float cosa = dot(normal_cam, light_cam);
	return clamp(cosa, 0.0, 1.0) * light_intensity;
}
