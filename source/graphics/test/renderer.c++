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

#include <aw/graphics/gl/material_manager.h>
#include <aw/graphics/gl/command_list.h>
#include <aw/graphics/gl/camera.h>
#include <aw/graphics/gl/render_context.h>
#include <aw/graphics/gl/uniform_buffer.h>

#include <aw/graphics/gl/utility/model/obj.h>
#include <aw/utility/on_scope_exit.h>
#include <aw/io/input_file_stream.h>
//#include <aw/utility/to_string/math/vector.h>
//#include <aw/utility/to_string/math/matrix.h>

#include <GLFW/glfw3.h>
#include <aw/utility/to_string.h>
namespace aw::gl3 {
using namespace std::string_view_literals;

program_manager pman;
texture_manager tman;
material_manager mman;


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
		gl3::program& program = mtl.prg;
		auto campos = ctx.camera_position;
		program[mtl.model_to_camera] = campos * pos;

		for (auto obj : model.objects)
			gl::draw_elements_base_vertex(GL_TRIANGLES, obj.num_elements, GL_UNSIGNED_INT, 0, obj.offset);
	}
};
std::vector<object> objects;
camera cam;

bool disable_rur = false;

namespace commands {
struct select_program {
	void operator()( render_context& ctx )
	{
		gl::use_program( program_handle{*prg} );
		ctx.set_program( *prg );
	}

	program* prg;
};

struct select_material {
	void operator()( render_context& ctx )
	{
		ctx.set_material( *mtl );
		mtl->bind_parameters();
		mtl->bind_textures();
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
	ctx.camera_position = math::identity_matrix<float,4>;

	common.emplace(common_block_idx, common_block_size);

	vec4 lint{ 1.0, 1.0, 1.0, 1.0 };
	vec3 ldir{ 0.577, 0.577, 0.577 };
	common->set_data(sizeof(mat4), lint.array(), ldir.array());


	size_t idx = 0;
	int count = 0;
	file >> count;
	while (count --> 0) {
		std::string vsh, fsh;
		file >> vsh >> fsh;
		idx = pman.create_program( vsh, fsh ) + 1;
	}

	for (int i = 0; i < idx; ++i) {
		auto ref = pman[i];
		program& prg = ref;
		auto block = prg.uniform_block("common_data");
		common->bind(prg, block);
		mman.add_resource("rur",material{ pman[i] });
	}
	auto t = tman.create_texture("materials/butruck.png");
	mman[1].get().add_texture("the_textur", tman[t] );

	string_view paths[] {
		"materials/m/des_dirt1.png",
		"materials/m/des_redrockbot.png",
		"materials/m/des_redrockmid.png",
		"materials/m/des_rocky1.png",
		"materials/m/des_rocky1_dirt1.png",
		"materials/m/des_oldrunway.png",
		"materials/m/des_oldrunwayblend.png",
		"materials/m/des_panelconc.png",
		"materials/m/des_dirttrack1r.png",
		"materials/m/des_dirttrackl.png",
		"materials/m/des_dirttrackx.png",
		"materials/m/des_dirttrack1.png",
		"materials/m/des_1line256.png",
		"materials/m/des_dirt2blend.png",
		/*"materials/m/vgs_shopwall01_128.png",
		"materials/m/vgs_shopwall01_128.png",
		"materials/m/des_scrub1_dirt1.png",
		"materials/m/des_scrub1.png",
		"materials/m/Tar_1line256HV.png",
		"materials/m/desstones_dirt1.png",
		"materials/m/parking2plain.png",
		"materials/m/Tar_lineslipway.png",
		"materials/m/parking2.png",
		"materials/m/rocktbrn_dirt2.png",
		"materials/m/rocktbrn128.png",
		"materials/m/des_roadedge1.png",
		"materials/m/des_ranchwall1.png",
		"materials/m/vgs_shopwall01_128.png",
		"materials/m/vgs_shopwall01_128.png",
		"materials/m/des_redrock2.png",
		"materials/m/des_redrock1.png"*/
	};

	auto t2 = tman.create_texture_array( paths );
	mman[2].get().add_texture( "tex", tman[t2] );


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
			cmds.add( commands::select_program{ mman[t.mtl].get().prg.ptr() } );
			cmds.add( commands::select_material{ mman[t.mtl].ptr() } );
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
mat4 camera_transform = math::identity_matrix<float,4>;

void update_camera(GLFWwindow* window, std::chrono::duration<float> frame_time)
{
	float horiz = (2.0f * mx) / hx - 1.0f;
	float vert  = 1.0f - (2.0f * my) / hy;
	auto pitch = math::pitch_matrix( degrees<float>(90) * vert );
	auto yaw   = math::yaw_matrix( degrees<float>(180)  * horiz );

	mat4 rot = math::identity_matrix<float,4>;
	rot = pitch * yaw;

	struct {
		GLFWwindow* window;
		bool num[10] = {
			glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS,
			glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS,
			glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS,
			glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS,
			glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS,
			glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS,
			glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS,
			glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS,
			glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS,
			glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS
		};
		bool d = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
		bool a = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
		bool q = glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS;
		bool e = glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;
		bool z = glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS;
		bool c = glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS;
		bool w = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
		bool s = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
		bool S = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)   == GLFW_PRESS;
		bool A = glfwGetKey(window, GLFW_KEY_LEFT_ALT)     == GLFW_PRESS;
		bool C = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;
	} keys{window};
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

	ctx.camera_position = rot * forward;
}

void render(GLFWwindow* window)
{
	using namespace std::chrono;
	static duration<double> period{1};
	static auto begin = steady_clock::now();
	static auto prev = begin;
	auto now = steady_clock::now();
	duration<double> elapsed   = now - begin;
	duration<float> frame_time = now - prev;
	prev = now;

	if (!disable_rur)
		update_camera(window, frame_time);

	clear();
	cmds.render(ctx);
	gl::use_program( gl::no_program );
}

} // namespace aw::gl3

namespace aw {
int main()
{
	using namespace gl3;

	glfwInit();
	auto guard = on_scope_exit{ glfwTerminate };

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(window);

	auto result = ::gl::sys::load_functions_3_3();
	std::cout << "GL loaded, missing: " << result.num_missing() << '\n';

	initialize_scene();
	reshape(800, 600);

	auto on_resize = [] (GLFWwindow*, int w, int h) {
		reshape(w,h);
	};
	auto on_mouse = [] (GLFWwindow* window, double x, double y) {
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		mx = x; my = double(h) - y;
	};
	auto on_key   = [] (GLFWwindow*, int key,int, int action, int) {
		if (action != GLFW_PRESS)
			return;
		if (key == GLFW_KEY_P) {
			auto m = *inverse(ctx.camera_position);
			std::cout << m[0][0] << ' ' << m[0][1] << ' ' << m[0][2] << ' ' << m[0][3] << '\n';
			std::cout << m[1][0] << ' ' << m[1][1] << ' ' << m[1][2] << ' ' << m[1][3] << '\n';
			std::cout << m[2][0] << ' ' << m[2][1] << ' ' << m[2][2] << ' ' << m[2][3] << '\n';
			std::cout << m[3][0] << ' ' << m[3][1] << ' ' << m[3][2] << ' ' << m[3][3] << '\n';
		} else if (key == GLFW_KEY_LEFT_BRACKET) {
			static unsigned i = 0;
			i = (i + 1) % objects.size();
			ctx.camera_position = *inverse(objects[i].pos);
		} else if (key == GLFW_KEY_RIGHT_BRACKET) {
			static unsigned i = 0;
			i = (i - 1) % objects.size();
			ctx.camera_position = *inverse(objects[i].pos);
		} else if (key == GLFW_KEY_O) {
			disable_rur = !disable_rur;
		}
	};
	glfwSetWindowSizeCallback(window, +on_resize );
	glfwSetCursorPosCallback(window,  +on_mouse );
	glfwSetKeyCallback(window,        +on_key );

	GLint num;
	gl::get_integerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &num);
	std::cout << "maxvert: " << num << '\n';
	gl::get_integerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &num);
	std::cout << "maxlayer: " << num << '\n';
	gl::get_integerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &num);
	std::cout << "maxblocks: " << num << '\n';
	

	size_t ctr  = 0;
	size_t prev = 0;
	using namespace std::chrono;
	auto start = steady_clock::now();
	auto point = start;
	float delto = 0.5;
	int min = std::numeric_limits<int>::max();
	int max = 0;
	int avg = 0;
	while (!glfwWindowShouldClose(window)) {
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
			std::string title = "FPS: " + to_string(avg) + "avg " + to_string(cur) + "cur " + to_string(max) + "max " + to_string(min) + "min";
			glfwSetWindowTitle(window, title.data());
			prev  = ctr;
		}

		glfwPollEvents();
		render(window);
		glfwSwapBuffers(window);
	}

	std::cout << "FPS (min/max/avg): " << min << '/' << max << '/' << avg << '\n';

}
} // namespace aw

int main()
{
	return aw::main();
}
