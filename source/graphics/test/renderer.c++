#include "camera_controller.h"

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

#include <GLFW/glfw3.h>

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
		"materials/m/vgs_shopwall01_128.png",
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
		"materials/m/des_redrock1.png"
	};

	for (auto [i,path] : ipairs(paths))
	{
		std::cout << path << ' ' << i << '\n';
	}

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

camera_controller camctl{ ctx.camera_position, cam };
static size_t cam_obj = 0;
void next_object()
{
	cam_obj = (cam_obj + 1) % objects.size();
	camctl.transform = *inverse(objects[cam_obj].pos);
}

void prev_object()
{
	cam_obj = (cam_obj - 1) % objects.size();
	camctl.transform = *inverse(objects[cam_obj].pos);
}


void reshape(int x, int y)
{
	gl::viewport(0, 0, x, y);

	camctl.screen = vec2{x,y};
	cam.set_aspect_ratio( float(x) / float(y) );

	auto proj = cam.projection_matrix();
	common->set_data(0, array(proj));
}

void clear()
{
	gl::clear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void render(GLFWwindow* window, std::chrono::duration<double> dt)
{
	camctl.frame( window, dt );

	clear();
	cmds.render(ctx);
	gl::use_program( gl::no_program );
}

} // namespace aw::gl3
