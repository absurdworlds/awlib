#ifndef aw_graphics_test_camera_controller_h
#define aw_graphics_test_camera_controller_h
#include <aw/graphics/glsl/vec.h>
#include <aw/graphics/glsl/mat.h>
#include <aw/graphics/gl/camera.h>
#include <chrono>

struct GLFWwindow;

namespace aw::gl3 {
struct camera_controller {
	mat4& out;
	camera& cam;

	mat4 transform = math::identity_matrix<float,4>;
	mat4 look_dir = math::identity_matrix<float,4>;
	vec2 screen;

	bool mouse_look = true;
	bool horiz_lock = false;

	void mouse_input(vec2 mouse);

	void frame(GLFWwindow* window, std::chrono::duration<float> frame_time);
};
} // namespace aw::gl3
#endif//aw_graphics_test_camera_controller_h
