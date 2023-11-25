#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ShaderManager.h"

using namespace ImGui;

class ImGuiManager
{
public:
	ImGuiManager();
	~ImGuiManager();

	void Initialize(GLFWwindow* mainWindow);
	void StartWindow(const char* text, float width, float height);

	void AddText(const char* text);
	void AddSliderInt(const char* text, int *value, int start, int end);
	void AddSliderFloat(const char* text, float* value, float start, float end);
	void AddColorPicker(const char* text, float* value);

	void FinishWindow();
	void RenderWindow();

private:

};

