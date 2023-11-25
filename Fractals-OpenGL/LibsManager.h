#pragma once

#include "ImGuiManager.h"
#include "Parameters.h"
#include <functional>

using namespace std;

class LibsManager
{
public:
	LibsManager();
	~LibsManager();
	void Initialize();

	template <typename Func>
	void SetResizeCallBack(Func callback) { glfwSetWindowSizeCallback(mainWindow, callback); }

	template <typename Func>
	void SetKeyCallBack(Func callback) { glfwSetKeyCallback(mainWindow, callback); }

	bool GetWindowShouldClose();
	void SwapBuffers();

	void StartGUI();
	void AddIntSlider(const char* text, int* value, int start, int end);
	void AddFloatSlider(const char* text, float* value, float start, float end);
	void AddVec2Slider(const char* text, vec2* value, float start, float end);
	void AddColorPicker(const char* text, float* value);
	void FinishGUI();
	void RenderGUI();

private:
	GLFWwindow* mainWindow;
	ImGuiManager* imGuiManager;

	void InitGLFW();
	void InitialiseWindow(const int width, const int height, const char* windowName);
	void InitGLEW();
};
