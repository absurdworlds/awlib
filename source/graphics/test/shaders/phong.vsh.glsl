#version 330
layout(location = 0) in vec4 position;
layout(location = 2) in vec3 normal;

smooth out vec3 frag_normal;
smooth out vec3 frag_pos;

uniform mat4 view_matrix;
uniform mat4 camtrafo;
uniform mat4 transform;

void main()
{
    mat4 modelview = camtrafo * transform;
    vec4 pos =  modelview * position;
    frag_pos = pos.xyz;
    frag_normal = mat3(modelview) * normal;
    gl_Position  = view_matrix * pos;
}
