#include "camera_controller.h"
#include <GLFW/glfw3.h>

namespace aw::gl3 {

/*
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
*/
void camera_controller::mouse_input(vec2 mouse)
{
	if (!mouse_look)
		return;
	float horiz = (2.0f * mouse.x()) / screen.x() - 1.0f;
	float vert  = 1.0f - (2.0f * mouse.y()) / screen.y();

	auto pitch = math::pitch_matrix( degrees<float>(90) * vert );
	auto yaw   = math::yaw_matrix( degrees<float>(180)  * horiz );
	look_dir = pitch * yaw;
}

void camera_controller::frame(GLFWwindow* window, std::chrono::duration<float> frame_time)
{
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

	float speed = 10.0f;
	if (S) speed *= 10.0f;
	if (A) speed *= 100.0f;
	if (C) speed /= 10.0f;

	vec4 movement{
		float(a - d),
		float(z - c),
		float(w - s),
		0
	};
	movement *= frame_time.count() * speed;
	movement = movement * look_dir;
	//this is equivalent to:
	//movement = math::transpose(look_dir) * movement;

	radians<float> ang { frame_time.count() * 5 * (q - e) };
	auto rotation = math::identity_matrix<float, 4>;
	rotation = math::yaw_matrix( -ang );

	transform.get(0,3) += movement[0];
	transform.get(1,3) += movement[1];
	transform.get(2,3) += movement[2];
	transform = rotation * transform;

	if (mouse_look)
		out = look_dir * transform;
	else
		out = transform;
}

} // namespace aw::gl3
