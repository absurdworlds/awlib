#include <aw/graphics/gl/gl_ext33.h>
#include <aw/types/string_view.h>
#include <aw/utility/string/split.h>
#include <aw/math/matrix3.h>
#include <aw/math/matrix4.h>
#include <aw/math/math.h>
#include <aw/math/angle.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

#include <aw/graphics/gl/shader.h>
#include <aw/graphics/gl/program.h>
#include <aw/graphics/gl/model.h>

#include <aw/graphics/gl/shader_file.h>
#include <aw/graphics/gl/camera.h>
#include <aw/fileformat/obj/loader.h>
#include <aw/io/input_file_stream.h>
#include <aw/utility/to_string/math/vector.h>
#include <aw/utility/to_string/math/matrix.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <aw/utility/to_string.h>
namespace aw::gl3 {
using namespace std::string_view_literals;

optional<program> test_program;
uniform_location perspective_location;
uniform_location transform_location;
uniform_location screen_location;
uniform_location time_location;
uniform_location period_location;
uniform_location campos_location;

camera cam;

void initialize_program()
{
	std::vector<shader> shaderList;

	auto vsh = load_shader( gl::shader_type::vertex,   "vert6.glsl" );
	auto fsh = load_shader( gl::shader_type::fragment, "frag1.glsl" );

	if (vsh && fsh) {
		shaderList.push_back(std::move(*vsh));
		shaderList.push_back(std::move(*fsh));
	}

	test_program = program();
	test_program->link( shaderList );

	auto& program = *test_program;

	screen_location = program.uniform("screen");
	time_location   = program.uniform("time");
	period_location = program.uniform("period");
	campos_location = program.uniform("camera");
	perspective_location = program.uniform("perspective");
	transform_location   = program.uniform("transform");

	gl::use_program( underlying(program_handle{program}) );

	cam.set_near_z(1.0f);
	cam.set_far_z(10000.0f);

	cam.set_aspect_ratio(1.0f);
	cam.set_fov( degrees<float>{90} );

	program["perspective"] = cam.projection_matrix();

	gl::use_program( 0 );
}



std::vector<model> models;
void load_model( string_view filename )
{
	io::input_file_stream file{ filename };
	auto data = obj::mesh::parse( file );

	std::vector< float > verts;
	std::vector< u16 > indices;

	for (auto v : data.verts) {
		verts.push_back( v[0] );
		verts.push_back( v[1] );
		verts.push_back( v[2] );
	}

	size_t color_offset = verts.size()*sizeof(float);

	for (auto v : data.verts) {
		verts.push_back( 0.5 );
		verts.push_back( 0.5 );
		verts.push_back( 0.5 );
		verts.push_back( 1.0 );
	}

	for (auto t : data.faces) {
		indices.push_back( t.verts[0].index );
		indices.push_back( t.verts[1].index );
		indices.push_back( t.verts[2].index );
	}

	vert_data vd{ verts, 0, color_offset };
	mesh_data md{ indices };

	models.emplace_back( vd, md );
}

struct object {
	size_t model_id;
	mat4   pos;

	void render(gl3::program& program)
	{
		auto& model = models[model_id];

		gl::bind_vertex_array(model.vao);
		program[transform_location] = pos;

		for (auto obj : model.objects)
			gl::draw_elements_base_vertex(GL_TRIANGLES, obj.num_elements, GL_UNSIGNED_SHORT, 0, obj.offset);
	}
};
std::vector<object> objects;

void initialize_scene()
{
	load_model("testworld.obj");
	load_model("butruck.obj");

	object world;
	world.model_id = 0;
	world.pos = math::identity_matrix<float,4>;
	object btrk;
	btrk.model_id = 1;
	btrk.pos = math::identity_matrix<float,4>;
	btrk.pos = math::yaw_matrix( degrees<float>{ 180.0f } );
	btrk.pos.get(1,3) = 3.0;

	objects.push_back(world);
	objects.push_back(btrk);

	gl::enable(GL_CULL_FACE);
	gl::cull_face(GL_BACK);
	gl::front_face(GL_CCW);

	gl::enable(GL_DEPTH_TEST);
	gl::depth_mask(GL_TRUE);
	gl::depth_func(GL_LEQUAL);
	gl::depth_range(0.0f, 1.0f);
}

int mx, my;
int hx, hy;


void reshape(int x, int y)
{
	gl::viewport(0, 0, x, y);

	hx = x;
	hy = y;
	cam.set_aspect_ratio( float(x) / float(y) );
}

void clear()
{
	gl::clear_color( 1.0f, 1.0f, 1.0f, 1.0f );
	gl::clear_depth( 1.0f );
	gl::clear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void calc_positions()
{
	//static std::vector<float> vec;
	//vec.assign(std::begin(cube), std::end(cube));

	// gl::bind_buffer( GL_ARRAY_BUFFER, pbo );
	// gl::buffer_sub_data( GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vec.data() );
}

float xx,yy,zz;
mat4 camera_transform = math::identity_matrix<float,4>;
vec3 campos {};

void render()
{
	using namespace std::chrono;
	static duration<double> period{1};
	static auto begin = steady_clock::now();
	static auto prev = begin;
	auto now = steady_clock::now();
	duration<double> elapsed   = now - begin;
	duration<float> frame_time = now - prev;
	prev = now;


	clear();


	auto& program = *test_program;
	gl::use_program( underlying(program_handle{program}) );
	program[screen_location] = vec2{ float(hx), float(hy) };

	program[perspective_location] = cam.projection_matrix();
	program[period_location] = period.count();
	program[time_location]   = elapsed.count();


	float horiz = (2.0f * mx) / hx - 1.0f;
	float vert  = 1.0f - (2.0f * my) / hy;
	auto pitch = math::pitch_matrix( degrees<float>(90) * vert );
	auto yaw   = math::yaw_matrix( degrees<float>(180)  * horiz );

	mat4 rot = math::identity_matrix<float,4>;
	rot = pitch * yaw;

	struct {
		bool d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		bool a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		bool q = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
		bool z = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
		bool w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		bool s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		bool S = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
		bool C = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
	} keys;
	float S = 1.0f;
	if (keys.S) S *= 10.0f;
	if (keys.C) S *= 100.0f;
	vec4 movement{
		S * (keys.a - keys.d),
		S * (keys.z - keys.q),
		S * (keys.w - keys.s),
		0
	};
	auto fvec = float(frame_time.count()) * movement * rot;

	static size_t frame_ctr = 0;
	//std::cout << "frame: " << frame_ctr++ << '\n';
	//std::cout << to_string(fvec) << '\n';
	//std::cout << 90 * vert << ' ' << 180 * horiz << '\n';

	auto& forward = camera_transform;
	forward.get(0,3) += fvec[0];
	forward.get(1,3) += fvec[1];
	forward.get(2,3) += fvec[2];

	program[campos_location] = rot * forward;

	for (auto& obj : objects)
		obj.render(program);
	
	gl::use_program( 0 );
}

} // namespace aw::gl3

namespace aw {
int main()
{
	using namespace gl3;
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.attributeFlags = sf::ContextSettings::Core;
	settings.majorVersion = 3;
	settings.minorVersion = 3;

	sf::Window window(sf::VideoMode(800, 600), "GL tut", sf::Style::Default, settings);

	auto result = gl::sys::load_functions_3_3();
	std::cout << "GL loaded, missing: " << result.num_missing() << '\n';

	initialize_program();
	initialize_scene();
	reshape(800, 600);

	GLint num;
	gl::get_integerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &num);
	std::cout << "maxvert: " << num << '\n';

	size_t ctr  = 0;
	size_t prev = 0;
	using namespace std::chrono;
	auto start = steady_clock::now();
	auto point = start;
	float delto = 0.5;
	int min = std::numeric_limits<int>::max();
	int max = 0;
	int avg = 0;
	while (window.isOpen()) {
		sf::Event event;
		int x,y;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized) {
				reshape(event.size.width, event.size.height);
				x = event.size.width;
				y = event.size.height;
			}
			if (event.type == sf::Event::MouseMoved) {
				mx = sf::Mouse::getPosition(window).x;
				my = sf::Mouse::getPosition(window).y;

				my = window.getSize().y - my;
			}
			/*if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::U)
					zz -= delto;
				if (event.key.code == sf::Keyboard::J)
					zz += delto;
				if (event.key.code == sf::Keyboard::Q)
					yy -= delto;
				if (event.key.code == sf::Keyboard::Z)
					yy += delto;
				if (event.key.code == sf::Keyboard::D)
					xx -= delto;
				if (event.key.code == sf::Keyboard::A)
					xx += delto;
				if (event.key.code == sf::Keyboard::R)
					delto += 0.5;
				if (event.key.code == sf::Keyboard::T)
					delto -= 0.5;
				std::cout << xx << ' ' << yy << ' ' << zz << ' ' << delto << '\n';
			}*/
		}
		++ctr;
		auto now = steady_clock::now();
		if ((now - point) >= seconds{1}) {
			duration<double> immed = now - point;
			duration<double> total = now - start;
			point = now;

			avg = int(ctr / total.count());
			int cur = int((ctr - prev) / immed.count());
			if (cur < min)
				min = cur;
			if (cur > max)
				max = cur;
			window.setTitle( "FPS: " + to_string(avg) + "avg " + to_string(cur) + "cur " + to_string(max) + "max " + to_string(min) + "min");
			prev  = ctr;
		}

		render();

		window.display();
	}

	std::cout << "FPS (min/max/avg): " << min << '/' << max << '/' << avg << '\n';
}
} // namespace aw

int main()
{
	return aw::main();
}
