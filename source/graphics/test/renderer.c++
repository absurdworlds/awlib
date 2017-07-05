#include <aw/graphics/gl/awgl/api.h>
#include <aw/types/string_view.h>
#include <aw/utility/string/split.h>
#include <aw/math/matrix3.h>
#include <aw/math/matrix4.h>
#include <aw/math/math.h>
#include <aw/math/angle.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <chrono>

#include <aw/graphics/gl/shader.h>
#include <aw/graphics/gl/program.h>
#include <aw/graphics/gl/model.h>

#include <aw/graphics/gl/shader_file.h>
#include <aw/graphics/gl/utility/model/obj.h>
#include <aw/graphics/gl/camera.h>
#include <aw/io/input_file_stream.h>
#include <aw/utility/to_string/math/vector.h>
#include <aw/utility/to_string/math/matrix.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <aw/utility/to_string.h>
namespace aw::gl3 {
using namespace std::string_view_literals;

struct material {
	// TODO: this isn't a mockup of an actual material
	// this will be some kind of wrapper over program,
	// since it makes sense that common uniforms belong
	// to a program, not to material
	// TODO: some of them, like screen and time will be
	// replaced by UBOs
	gl3::program program;
	uniform_location perspective_location;
	uniform_location transform_location;
	uniform_location screen_location;
	uniform_location time_location;
	uniform_location period_location;
	uniform_location campos_location;

	//TODO: I wanted to place this outside of class,
	//but right now that is not very convenient
	std::vector<size_t> objects;

	void render();
};
std::vector<material> materials;

void load_program( string_view v, string_view f)
{
	std::vector<shader> shaderList;

	auto vsh = load_shader( gl::shader_type::vertex,   v );
	auto fsh = load_shader( gl::shader_type::fragment, f );

	if (vsh && fsh) {
		shaderList.push_back(std::move(*vsh));
		shaderList.push_back(std::move(*fsh));
	}

	material tmp;
	auto& program = tmp.program;
	program.link( shaderList );

	tmp.screen_location = program.uniform("screen");
	tmp.time_location   = program.uniform("time");
	tmp.period_location = program.uniform("period");
	tmp.campos_location = program.uniform("camera");
	tmp.perspective_location = program.uniform("perspective");
	tmp.transform_location   = program.uniform("transform");

	materials.emplace_back( std::move(tmp) );
}



std::vector<model> models;
void load_model( string_view filename )
{
	io::input_file_stream file{ filename };
	auto data = obj::mesh::parse( file );
	models.emplace_back( model_from_obj(data) );
}

struct object {
	size_t model_id;
	mat4   pos;

	void render(material& mtl)
	{
		auto& model = models[model_id];

		gl::bind_vertex_array(model.vao);
		mtl.program[mtl.transform_location] = pos;

		for (auto obj : model.objects)
			gl::draw_elements_base_vertex(GL_TRIANGLES, obj.num_elements, GL_UNSIGNED_INT, 0, obj.offset);
	}
};
std::vector<object> objects;
camera cam;

void initialize_scene()
{
	std::fstream file{ "scene.txt" };

	cam.set_near_z(0.5f);
	cam.set_far_z(5000.0f);

	cam.set_aspect_ratio(1.0f);
	cam.set_fov( degrees<float>{90} );

	int count = 0;
	file >> count;
	while (count --> 0) {
		std::string vsh, fsh;
		file >> vsh >> fsh;
		load_program( vsh, fsh );
	}

	file >> count;
	while (count --> 0) {
		std::string name;
		file >> name;
		load_model( name );
	}

	auto push_object = [] (object& obj, size_t mtl) {
		materials[mtl].objects.push_back(objects.size());
		objects.push_back(obj);
	};
	file >> count;
	while (count --> 0) {
		vec3 pos, rot;
		int mat, mdl;
		file >> mat >> mdl;
		file >> pos[0] >> pos[1] >> pos[2];
		file >> rot[0] >> rot[1] >> rot[2];
		object o;
		o.model_id = mdl;
		o.pos = math::identity_matrix<float,4>;
		auto deg = math::vector3d<degrees<float>>( rot );
		o.pos = math::matrix_from_euler( deg );
		o.pos.get(0,3) = pos[0];
		o.pos.get(1,3) = pos[1];
		o.pos.get(2,3) = pos[2];
		push_object(o, mat);
	}

	gl::enable(GL_CULL_FACE);

	gl::cull_face(GL_BACK);
	gl::front_face(GL_CCW);

	gl::enable(GL_DEPTH_TEST);
	gl::depth_mask(GL_TRUE);
	gl::depth_func(GL_LEQUAL);
	gl::depth_range(0.0f, 1.0f);

	gl::clear_color( 1.0f, 1.0f, 1.0f, 1.0f );
	gl::clear_depth( 1.0f );
	gl::clear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
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


	auto campos = rot * forward;

	clear();

	for (auto& mtl : materials) {
		auto& program = mtl.program;
		gl::use_program( program_handle{program} );
		program[mtl.screen_location] = vec2{ float(hx), float(hy) };

		program[mtl.perspective_location] = cam.projection_matrix();
		program[mtl.period_location] = period.count();
		program[mtl.time_location]   = elapsed.count();
		program[mtl.campos_location] = campos;

		program["light_dir"] = vec3{ 0.577, 0.577, 0.577 };
		program["light_intensity"] = vec4{ 1.0, 1.0, 1.0, 1.0 };

		for (auto& obj : mtl.objects)
			objects[obj].render(mtl);

	}

	gl::use_program( gl::no_program );
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

	auto result = ::gl::sys::load_functions_3_3();
	std::cout << "GL loaded, missing: " << result.num_missing() << '\n';

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
