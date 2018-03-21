#version 330
smooth in vec4 lightness;
in vec2 f_texCoord;
flat in float matid;

out vec4 outputColor;

uniform sampler2DArray tex;

void main()
{
	outputColor = texture(tex, vec3(f_texCoord, matid)) * lightness;
}
