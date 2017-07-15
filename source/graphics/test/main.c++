#include <aw/graphics/gl/render_context.h>
#include <aw/graphics/gl/awgl/api.h>
#include <aw/graphics/glsl/vec.h>
#include <aw/graphics/glsl/mat.h>

#include <aw/utility/on_scope_exit.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

namespace aw {
using namespace std::chrono;
namespace gl3 {
extern bool disable_rur;
extern int mx, my;
extern render_context ctx;
void initialize_scene();
void reshape(int x, int y);
void render(GLFWwindow*, duration<double>);
}
using namespace gl3;

inline void print_matrix(mat4 const& m)
{
	auto println = [] (auto const&... val) {
		( std::cout << ... << val ) << '\n';
	};

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
	std::string title = "FPS: " +
	                    to_string(avg) + "avg " +
	                    to_string(cur) + "cur " +
	                    to_string(max) + "max " +
	                    to_string(min) + "min";

	glfwSetWindowTitle(window, title.data());

	last_refresh = now;
	last_frames = frames;
}

int main()
{
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
			print_inverse_matrix(ctx.camera_position);
		} else if (key == GLFW_KEY_LEFT_BRACKET) {
			/*static unsigned i = 0;
			i = (i + 1) % objects.size();
			ctx.camera_position = *inverse(objects[i].pos);*/
		} else if (key == GLFW_KEY_RIGHT_BRACKET) {
			/*static unsigned i = 0;
			i = (i - 1) % objects.size();
			ctx.camera_position = *inverse(objects[i].pos);*/
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

int main()
{
	return aw::main();
}
