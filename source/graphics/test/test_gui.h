#ifndef TEST_GUI_H
#define TEST_GUI_H

#include <GLFW/glfw3.h>

void init_imgui(GLFWwindow* window);
void render_imgui(GLFWwindow *window);
void onkey_imgui(GLFWwindow* window, int key, int scancode, int action, int mods);
void shutdown_imgui();

#endif // TEST_GUI_H
