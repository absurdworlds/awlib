#include "camera_controller.h"

#include <aw/graphics/gl/render_context.h>
#include <aw/graphics/gl/awgl/api.h>
#include <aw/graphics/glsl/vec.h>
#include <aw/graphics/glsl/mat.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

namespace aw {
using namespace std::chrono;
namespace gl3 {
extern render_context ctx;
extern camera_controller camctl;

void initialize_scene();
void reshape(int x, int y);
void render(GLFWwindow*, duration<double>);
void next_object();
void prev_object();
}
using namespace gl3;

auto println = [] (auto const&... val) {
	( std::cout << ... << val ) << '\n';
};

inline void print_matrix(mat4 const& m)
{
	println( m[0][0], ' ', m[0][1], ' ', m[0][2], ' ', m[0][3] );
	println( m[1][0], ' ', m[1][1], ' ', m[1][2], ' ', m[1][3] );
	println( m[2][0], ' ', m[2][1], ' ', m[2][2], ' ', m[2][3] );
	println( m[3][0], ' ', m[3][1], ' ', m[3][2], ' ', m[3][3] );
}

inline void print_inverse_matrix(mat4 const& mat)
{
	auto inv = inverse(mat);
	if (inv)
		print_matrix(*inv);
	else
		std::cout << "inverse matrix does not exist!\n";
}

static constexpr auto refresh_rate = seconds{1};
static int min = std::numeric_limits<int>::max();
static int max = 0;
static int avg = 0;
void frame_ctr( GLFWwindow* window, steady_clock::time_point now )
{
	static size_t frames = 0;
	static size_t last_frames = 0;
	static auto start        = now;
	static auto last_refresh = now;

	++frames;

	if (now - last_refresh < refresh_rate)
		return;

	int cur = (frames - last_frames) / refresh_rate.count();
	min = std::min(min, cur);
	max = std::max(max, cur);

	duration<double> run_time = now - start;
	avg = frames / run_time.count();

	using std::to_string;
	std::string title = "FPS: ";
	title += to_string(avg) + "avg ";
	title += to_string(cur) + "cur ";
	title += to_string(max) + "max ";
	title += to_string(min) + "min";

	glfwSetWindowTitle(window, title.data());

	last_refresh = now;
	last_frames = frames;
}

GLFWwindow* create_window()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	auto window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
	return window;
}

void create_context( GLFWwindow* window )
{
	glfwMakeContextCurrent(window);

	auto result = ::gl::sys::load_functions_3_3();
	std::cout << "GL loaded, missing: " << result.num_missing() << '\n';
}

void print_capabilities( )
{
	GLint num;
	gl::get_integer_v(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &num);
	println( "GL_MAX_VERTEX_UNIFORM_COMPONENTS: ", num );
	gl::get_integer_v(GL_MAX_ARRAY_TEXTURE_LAYERS, &num);
	println( "GL_MAX_ARRAY_TEXTURE_LAYERS:      ", num );
	gl::get_integer_v(GL_MAX_VERTEX_UNIFORM_BLOCKS, &num);
	println( "GL_MAX_VERTEX_UNIFORM_BLOCKS:     ", num );
}


void main()
{
	GLFWwindow* window = create_window();

	create_context( window );
	print_capabilities();
	initialize_scene();
	reshape(800, 600);

	auto on_resize = [] (GLFWwindow*, int w, int h) {
		reshape(w,h);
	};
	auto on_mouse = [] (GLFWwindow* window, double x, double y) {
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		camctl.mouse_input( vec2{x, double(h) - y} );
	};
	auto on_key   = [] (GLFWwindow*, int key,int, int action, int) {
		if (action != GLFW_PRESS)
			return;
		if (key == GLFW_KEY_P) {
			print_inverse_matrix(ctx.camera_position);
		} else if (key == GLFW_KEY_LEFT_BRACKET) {
			next_object();
		} else if (key == GLFW_KEY_RIGHT_BRACKET) {
			prev_object();
		} else if (key == GLFW_KEY_O) {
			camctl.mouse_look = !camctl.mouse_look;
		}
	};
	glfwSetWindowSizeCallback(window, +on_resize );
	glfwSetCursorPosCallback(window,  +on_mouse );
	glfwSetKeyCallback(window,        +on_key );
	

	auto last_frame = steady_clock::now();

	while (!glfwWindowShouldClose(window)) {
		auto now = steady_clock::now();

		glfwPollEvents();
		render(window, now - last_frame);
		frame_ctr( window, now );
		last_frame = now;
		glfwSwapBuffers(window);
	}

	std::cout << "FPS (min/max/avg): " << min << '/' << max << '/' << avg << '\n';

}
} // namespace aw

#include <aw/fileformat/png/log.h>
#include <aw/log/ostream_logger.h>
namespace aw {
ostream_logger ologger{std::cerr};

static void set_loggers()
{
	png::log.set_logger(&ologger);
}
} // namespace aw

int main()
{
	glfwInit();
	aw::set_loggers();
	aw::main();
	glfwTerminate();
}
