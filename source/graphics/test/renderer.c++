#include "camera_controller.h"
#include "scene.h"

#include <aw/graphics/gl/awgl/api.h>
#include <aw/types/string_view.h>
#include <aw/utility/string/split.h>
#include <aw/math/matrix3.h>
#include <aw/math/matrix4.h>
#include <aw/math/transform.h>
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

#include <aw/utility/on_scope_exit.h>
#include <aw/io/input_file_stream.h>

#include <GLFW/glfw3.h>

namespace aw::gl3 {
using namespace std::string_view_literals;


void object::render(render_context& ctx)
{
	auto& mtl = *ctx.active_material;
	auto& model = scene->models[model_id];

	gl::bind_vertex_array(model.vao);
	gl3::program& program = mtl.prg;
	auto campos = ctx.camera_position;
	program[mtl.model_to_camera] = campos * pos;

	for (auto obj : model.objects)
		gl::draw_elements_base_vertex(GL_TRIANGLES, obj.num_elements, GL_UNSIGNED_INT, 0, obj.offset);
}

scene  scn;
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

	scn.load("scene.hdf");

	for (int i = 0; i < scn.pman.count(); ++i) {
		auto ref = scn.pman[i];
		program& prg = ref;
		auto block = prg.uniform_block("common_data");
		common->bind(prg, block);
	}

	auto compare = [] (const object& a, const object& b) {
		return (a.material_id < b.material_id) || (a.material_id == b.material_id && a.model_id < b.model_id);
	};
	std::sort(begin(scn.objects),end(scn.objects),compare);

	size_t prev_mtl = -1;
	for (auto& obj : scn.objects) {
		if (prev_mtl != obj.material_id) {
			cmds.add( commands::select_program{ scn.mman[obj.material_id].get().prg.ptr() } );
			cmds.add( commands::select_material{  scn.mman[obj.material_id].ptr() } );
		}
		prev_mtl = obj.material_id;
		cmds.add( commands::render_simple_object{ &obj } );
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
	cam_obj = (cam_obj + 1) % scn.objects.size();
	camctl.transform = *inverse(scn.objects[cam_obj].pos);
}

void prev_object()
{
	cam_obj = (cam_obj - 1) % scn.objects.size();
	camctl.transform = *inverse(scn.objects[cam_obj].pos);
}


void reshape(int x, int y)
{
	gl::viewport(0, 0, x, y);

	float fx = x;
	float fy = y;

	camctl.screen = vec2{fx,fy};
	cam.set_aspect_ratio( fx / fy );

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
