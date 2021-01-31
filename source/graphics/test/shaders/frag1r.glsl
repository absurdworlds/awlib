#version 330
smooth in vec4 theColor;
noperspective in float outDepth;

out vec4 outputColor;

void main()
{
	outputColor = theColor * vec4(1,0,0,1);
}
