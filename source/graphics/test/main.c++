#include <aw/graphics/gl/render_context.h>
#include <aw/graphics/gl/awgl/api.h>
#include <aw/graphics/glsl/vec.h>
#include <aw/graphics/glsl/mat.h>

#include <aw/utility/on_scope_exit.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

namespace aw {
namespace gl3 {
extern bool disable_rur;
extern int mx, my;
extern render_context ctx;
void initialize_scene();
void reshape(int x, int y);
void render(GLFWwindow*, std::chrono::duration<double>);
}
using namespace gl3;


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
	

	size_t ctr  = 0;
	size_t prev = 0;
	using namespace std::chrono;
	auto start = steady_clock::now();
	auto last_frame  = start;
	auto last_sample = start;

	int min = std::numeric_limits<int>::max();
	int max = 0;
	int avg = 0;

	while (!glfwWindowShouldClose(window)) {
		auto now = steady_clock::now();

		glfwPollEvents();
		render(window, now - last_frame);

		++ctr;
		if ((now - last_sample) >= milliseconds{200}) {
			duration<double> immed = now - last_sample;
			duration<double> total = now - start;
			last_sample = now;

			avg = int(ctr / total.count());
			int cur = int((ctr - prev) / immed.count());

			if (cur < min) min = cur;
			if (cur > max) max = cur;

			using std::to_string;
			std::string title = "FPS: " +
				to_string(avg) + "avg " +
				to_string(cur) + "cur " +
				to_string(max) + "max " +
				to_string(min) + "min";
			glfwSetWindowTitle(window, title.data());
			prev  = ctr;
		}

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
