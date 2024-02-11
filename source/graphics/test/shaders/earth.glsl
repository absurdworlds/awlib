#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

smooth out vec4 theColor;
noperspective out float outDepth;

layout(std140) uniform common_data {
	uniform mat4 perspective;
	uniform vec4 light_intensity;
	uniform vec3 light_dir;
};

uniform mat4 transform;
uniform mat4 campos;
uniform float curwa;

void main()
{
	mat4 camcam = campos;
	vec4 camera = inverse(camcam)[3];
	vec4 world_pos = transform   * position;
	vec4 camrel = world_pos - camera;

	/*float h = 0.7;
	if (h != 0.8) {
		float y = world_pos.y;
		float z = world_pos.z;
		float om = -1*sin(((worldpos.z) / 6300.0));
		float wy = z*sin(om)+y*cos(om); 
		float wz = z*cos(om)+y*sin(om);
		if (wy < world_pos.y)
			world_pos.y = wy;
		world_pos.z = wz;
	}
	if (h != 0.8) {
		float y = world_pos.y;
		float x = world_pos.x;
		float om = -1*sin(((worldpos.x) / 6300.0));
		float wy = x*sin(om)+y*cos(om);
		float wx = x*cos(om)+y*sin(om);
		if (wy < world_pos.y)
			world_pos.y = wy;
		world_pos.x = wx;
	}*/

	//float r = 6378137;
	//float r = 17370;
	float r = curwa;
	//float dist = camrel.x*camrel.x+camrel.z*camrel.z;
	//float down = dist/r;
	float dist = length(camrel.xz);
	float down = r - r*cos(dist/r);
	if (down > 0)
		world_pos.y -= down;

	/*vec4 o = vec4(camrel.x,0,camrel.z,0);
	o = normalize(o);

	world_pos += r * sin(dist/r) * o;*/

	vec4 cam_pos   = campos      * world_pos;
	//cam_pos.z -= r*sin(dist/r);

	vec4 clip_pos  = perspective * cam_pos;

	//vec3 normal_world = mat3(transform) * normal;
	vec3 normal_cam   = mat3(transform)    * normal;

	//vec3 light_world = mat3(transform) * light_dir;
	vec3 light_cam   = mat3(transform)    * light_dir;

	normal_cam = normalize(normal_cam);
	float cosa = dot(normal_cam, light_cam);
	cosa = clamp(cosa, 0, 1);

	outDepth = clip_pos.w;
	gl_Position = clip_pos;
	//float redness = length(camera - world_pos)/100;
	float blueness = length(camera - world_pos)/50000;
	vec4 color1= light_intensity * vec4(0.5,0.5,0.5,1)* cosa;
	vec4 color2= vec4(0.9,0.9,1.0,1);
	theColor = mix(color1,color2,min(blueness,1.0)) ;// + vec4(0.2,0.2,0.2,1);
}
