#version 330
out vec4 out_color;

smooth in vec3 frag_normal;
smooth in vec3 frag_pos;

struct dir_light {
	uniform vec4 intensity;
	uniform vec3 dir;
};

struct point_light {
	uniform float power;
	uniform vec3  pos;
	uniform vec3  color;
};

uniform float shininess;
uniform float attenuation;

float attenuate(in vec3 frag_pos, in vec3 light_pos, out vec3 light_dir)
{
        vec3 diff =  light_pos - frag_pos;
        float dist_sqr = dot(diff, diff);
        light_dir = diff * inversesqrt(dist_sqr);

        return (1 / ( 1.0 + attenuation * (dist_sqr)));
}

const vec3 specular_color = vec3(0.25, 0.25, 0.25);
void main()
{
    vec3 light_dir = vec3(0);
	float intensity = light_power * attenuate( frag_pos, light_dir );

    vec3 norm = normalize(frag_normal);
    float cos_a = dot(norm, light_dir);
    cos_a = max(cos_a, 0.0);

    vec3 eye_dir = normalize(-frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm );
    float phong = dot(eye_dir, reflect_dir);
    phong = max(phong, 0.0);
    phong = cos_a > 1.0e-5 ? phong : 0.0;
    phong = pow(phong, shininess);

    vec3 diffuse = light_color * intensity * cos_a;
    vec3 specular = specular_color * intensity * phong;
    out_color =  vec4(0.1) + vec4(diffuse,1) + vec4(specular,1);
}
