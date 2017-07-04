#version 330
smooth in vec4 theColor;
noperspective in float outDepth;

out vec4 outputColor;
uniform vec2 screen;
uniform float time;
uniform float period;

void main()
{
	outputColor = theColor;
}
