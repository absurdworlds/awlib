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

#include <aw/graphics/gl/command_list.h>
#include <aw/graphics/gl/render_context.h>
#include <aw/graphics/gl/uniform_buffer.h>

#include <aw/graphics/gl/utility/model/obj.h>
#include <aw/io/input_file_stream.h>
//#include <aw/utility/to_string/math/vector.h>
//#include <aw/utility/to_string/math/matrix.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <aw/utility/to_string.h>
namespace aw::gl3 {
using namespace std::string_view_literals;

program_manager pman;
material_manager mtls;


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

	void render( render_context& ctx)
	{
		auto& mtl = *ctx.active_material;
		auto& model = models[model_id];

		gl::bind_vertex_array(model.vao);
		auto& program = *mtl.prg;
		auto campos = ctx.camera_position;
		program[mtl.model_to_camera] = campos * pos;

		for (auto obj : model.objects)
			gl::draw_elements_base_vertex(GL_TRIANGLES, obj.num_elements, GL_UNSIGNED_INT, 0, obj.offset);
	}
};
std::vector<object> objects;
camera cam;

namespace commands {
struct select_program {
	void operator()( render_context& ctx )
	{
		gl::use_program( program_handle{prg} );
		ctx.set_program( *prg );
	}

	program_ref prg;
};

struct select_material {
	void operator()( render_context& ctx )
	{
		ctx.set_material( *mtl );
	}

	material* mtl;
};

struct render_simple_object {
	void operator()( render_context& ctx )
	{
		obj->render( ctx );
	}

	object* obj;
};
} // namespace commands

command_list cmds;

render_context ctx;
GLuint common_block_idx  = 0;
size_t common_block_size = sizeof(mat4) + sizeof(vec3) + sizeof(vec4);
optional<uniform_buffer> common;

void initialize_scene()
{
	std::fstream file{ "scene.txt" };

	cam.set_near_z(0.5f);
	cam.set_far_z(5000.0f);

	cam.set_aspect_ratio(1.0f);
	cam.set_fov( degrees<float>{90} );

	ctx.active_camera = &cam;

	common.emplace(common_block_idx, common_block_size);

	vec4 lint{ 1.0, 1.0, 1.0, 1.0 };
	vec3 ldir{ 0.577, 0.577, 0.577 };
	common->set_data(sizeof(mat4), lint.array(), ldir.array());


	int i;
	gl::get_integerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &i);
	std::cout << i << '\n';

	size_t idx = 0;
	int count = 0;
	file >> count;
	while (count --> 0) {
		std::string vsh, fsh;
		file >> vsh >> fsh;
		idx = pman.create_program( vsh, fsh ) + 1;
		auto& prg  = *pman[idx];
		auto block = prg.uniform_block("common_data");
		common->bind(prg, block);
	}

	while (idx --> 0)
		mtls.materials.emplace_back(material{ pman[idx] });

	file >> count;
	while (count --> 0) {
		std::string name;
		file >> name;
		load_model( name );
	}

	struct tmp {
		size_t mtl;
		size_t obj;
	};
	std::vector<tmp> vec;


	auto push_object = [&] (object& obj, size_t mtl) {
		vec.push_back(tmp{mtl, objects.size()});
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

	auto compare = [] (tmp a, tmp b) {
		return (a.mtl < b.mtl) || (a.mtl == b.mtl && a.obj < b.obj);
	};

	std::sort(begin(vec),end(vec),compare);
	tmp prev{size_t(-1),size_t(-1)};
	for (auto t : vec) {
		if (prev.mtl != t.mtl) {
			cmds.cmds.emplace_back( commands::select_program{ mtls.materials[t.mtl].prg } );
			cmds.cmds.emplace_back( commands::select_material{ &mtls.materials[t.mtl] } );
		}
		cmds.add( commands::render_simple_object{ &objects[t.obj] } );
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

	auto proj = cam.projection_matrix();
	common->set_data(0, array(proj));
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
		bool num[10] = {
			//sf::Keyboard::isKeyPressed(sf::Keyboard::Num0),
			0,
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num1),
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num2),
			/*sf::Keyboard::isKeyPressed(sf::Keyboard::Num3),
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num4),
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num5),
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num6),
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num7),
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num8),
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)*/
		};
		bool d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		bool a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		bool q = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
		bool e = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
		bool z = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
		bool c = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
		bool w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		bool s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		bool S = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
		bool A = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt);
		bool C = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
	} keys;
	float S = 10.0f;
	if (keys.S) S *= 10.0f;
	if (keys.A) S *= 100.0f;
	if (keys.C) S /= 10.0f;
	vec4 movement{
		S * (keys.a - keys.d),
		S * (keys.z - keys.c),
		S * (keys.w - keys.s),
		0
	};
	radians<float> ang { frame_time.count() * 5 * (keys.e - keys.q) };
	auto fvec = frame_time.count() * movement * rot;

	static degrees<float> fov { 90.0 };
	auto rate = fov < degrees<float>{ 30 }  ? (fov.count()) :
	            fov > degrees<float>{ 150 } ? (180 - fov.count()) :
	            30;
	if (keys.num[1]) fov -= rate*degrees<float>{ frame_time.count() };
	if (keys.num[2]) fov += rate*degrees<float>{ frame_time.count() };

	cam.set_fov( fov );
	if (keys.num[1] - keys.num[2] != 0) {
		auto proj = cam.projection_matrix();
		common->set_data(0, array(proj));
	}

	static size_t frame_ctr = 0;
	//std::cout << "frame: " << frame_ctr++ << '\n';
	//std::cout << to_string(fvec) << '\n';
	//std::cout << 90 * vert << ' ' << 180 * horiz << '\n';

	auto& forward = camera_transform;
	auto rmat = math::identity_matrix<float,4>;
	rmat = math::yaw_matrix(ang);
	forward.get(0,3) += fvec[0];
	forward.get(1,3) += fvec[1];
	forward.get(2,3) += fvec[2];
	forward = rmat * forward;


	auto campos = rot * forward;
	ctx.camera_position = campos;

	clear();

	cmds.render(ctx);

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
