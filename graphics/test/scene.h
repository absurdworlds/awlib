#ifndef aw_scene_loader_h
#define aw_scene_loader_h

#include <aw/graphics/gl/material_manager.h>
#include <aw/graphics/gl/utility/model/obj.h>

namespace aw::gl3 {
struct scene;

// TODO: inverse so that object is passed into the render context, not vice versa
struct render_context;
struct object {
	gl3::scene* scene; // TODO: get rid of
	size_t model_id;
	size_t material_id;
	mat4   pos;

	void render( render_context& ctx);
};

// TODO: rework this into a proper resource system
struct scene
{
	program_manager  pman;
	texture_manager  tman;
	material_manager mman;

	std::vector<model> models;
	std::vector<object> objects;

	void load(string_view path);

	size_t load_model( string_view filename );
};
} // namespace aw::gl3

#endif // aw_scene_loader_h
