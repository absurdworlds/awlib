#version 330
smooth in vec4 theColor;
smooth attribute in vec2 f_texCoord;
asd;
out vec4 outputColor;

uniform sampler2DArray tex;
uniform int matid;

void main()
{
	outputColor = texture(tex, vec3(f_texCoord, float(matid))) * theColor;
}
