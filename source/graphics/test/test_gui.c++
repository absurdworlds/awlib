#include "test_gui.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void init_imgui(GLFWwindow *window)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	glfwSetWindowFocusCallback(window, ImGui_ImplGlfw_WindowFocusCallback);
	glfwSetCursorEnterCallback(window, ImGui_ImplGlfw_CursorEnterCallback);
	glfwSetMouseButtonCallback(window, ImGui_ImplGlfw_MouseButtonCallback);
	glfwSetScrollCallback(window, ImGui_ImplGlfw_ScrollCallback);
	//glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
	glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);
	glfwSetMonitorCallback(ImGui_ImplGlfw_MonitorCallback);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, false);
	ImGui_ImplOpenGL3_Init("#version 330");

}

void render_imgui(GLFWwindow *window)
{
	bool show_demo_window = true;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow(&show_demo_window);
	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void shutdown_imgui()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void onkey_imgui(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}
