#version 330
smooth in vec4 theColor;
noperspective in float outDepth;

out vec4 outputColor;
uniform vec2 screen;
uniform float time;
uniform float period;

void main()
{
	float factor = mod(time, period) / period;
	factor = factor > 0.5 ? 1 - factor : factor;
	vec4 color1 = mix(vec4(1,0,0,1), vec4(0,1,1,1), gl_FragCoord.x / screen.x);
	vec4 color2 = mix(vec4(0,0,1,1), vec4(1,1,0,1), gl_FragCoord.y / screen.y);
	vec4 color3 = mix(color1, color2, factor);

	float z = outDepth;
	float dr1 = 1 + 50;
	float dr2 = 1 - 50;
	float d1 = (2.0 * z - dr1) / (dr2);
	float d = (d1 * 0.5) + 0.5;

	outputColor = mix(theColor, color3, sin(time));
	outputColor.xyz *= d;
	outputColor.xyz = clamp(outputColor.xyz, 0.1, 1.0);
}
