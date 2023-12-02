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
	void AddText(const char* text);
	void AddIntSlider(const char* text, int* value, int start, int end);
	void AddFloatSlider(const char* text, float* value, float start, float end);
	void AddVec2Slider(const char* text, vec2* value, float start, float end);
	void AddColorPicker(const char* text, float* value);
	void AddCheckBox(const char* text, bool* value);
	void AddSameLine();
	void FinishGUI();
	void RenderGUI();
	double GetFPS();

private:
	GLFWwindow* mainWindow;
	ImGuiManager* imGuiManager;
	double lastTime = 0.0, fps;
	int frameCount = 0;

	void UpdateFPS();

	void InitGLFW();
	void InitOpenGL();
	void InitialiseWindow(const int width, const int height, const char* windowName);
	void InitGLEW();
};
