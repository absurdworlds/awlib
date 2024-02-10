#version 330
smooth in vec2 f_texCoord;

out vec4 outputColor;

uniform sampler2D tex;

void main()
{
	outputColor = 0.5*texture(tex, f_texCoord);
}
