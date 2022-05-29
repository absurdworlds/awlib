#version 330
smooth in vec4 lightness;
in vec2 f_texCoord;

out vec4 outputColor;
uniform sampler2D the_textur;

void main()
{
	outputColor = texture(the_textur, f_texCoord) * lightness;
}
