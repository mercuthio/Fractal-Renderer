#pragma once

#include "ImGuiManager.h"
#include "Parameters.h"
#include <functional>

using namespace std;

class LibsManager
{
public:
	LibsManager();
	~LibsManager() { delete m_imGuiManager; }
	void Initialize();

	template <typename Func>
	void SetResizeCallBack(Func callback) { glfwSetWindowSizeCallback(m_mainWindow, callback); }

	template <typename Func>
	void SetKeyCallBack(Func callback) { glfwSetKeyCallback(m_mainWindow, callback); }

	bool GetWindowShouldClose() { return glfwWindowShouldClose(m_mainWindow); }
	void SwapBuffers() { glfwSwapBuffers(m_mainWindow); }

	void StartGUI() { m_imGuiManager->StartWindow(CONF_WINDOW_NAME, (float)CONF_WIDTH, (float)CONF_HEIGHT); }
	void AddText(const char* text) { m_imGuiManager->AddText(text); }
	void AddIntSlider(const char* text, int* value, int start, int end) { m_imGuiManager->AddSliderInt(text, value, start, end); }
	void AddFloatSlider(const char* text, float* value, float start, float end) { m_imGuiManager->AddSliderFloat(text, value, start, end); }
	void AddVec2Slider(const char* text, vec2* value, float start, float end);
	void AddColorPicker(const char* text, float* value) { m_imGuiManager->AddColorPicker(text, value); }
	void AddCheckBox(const char* text, bool* value) { m_imGuiManager->AddCheckbox(text, value); }
	bool AddButton(const char* text) { return m_imGuiManager->AddButton(text); }
	void AddRestartZoomButton(const char* text);
	void AddTextField(const char* text, char* content) { m_imGuiManager->AddTextField(text, content); }
	void AddSameLine() { m_imGuiManager->AddSameLine(); }
	void FinishGUI() { m_imGuiManager->FinishWindow(); }
	void RenderGUI() { m_imGuiManager->RenderWindow(); }

	double GetFPS();

private:
	GLFWwindow* m_mainWindow;
	ImGuiManager* m_imGuiManager;
	double m_lastTime = 0.0, m_fps;
	int m_frameCount = 0;

	void InitGLFW();
	void InitOpenGL();
	void InitialiseWindow(const int width, const int height, const char* windowName);
	void InitGLEW();

	void UpdateFPS();
};
