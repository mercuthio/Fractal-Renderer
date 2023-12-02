#include "ImGuiManager.h"

ImGuiManager::ImGuiManager() {}

ImGuiManager::~ImGuiManager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
}

void ImGuiManager::Initialize(GLFWwindow* mainWindow)
{
    CreateContext();
    ImGuiIO& io = GetIO();
    (void)io;

    StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImGuiStyle& style = GetStyle();
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.FrameBorderSize = 0.000001f;
    style.WindowBorderSize = 0.000001;

    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
    style.Colors[ImGuiCol_Border] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.0f, 1.0f, 1.0f, 0.3f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);

    style.Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
}

void ImGuiManager::StartWindow(const char* text, float width, float height)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();

    SetNextWindowPos(ImVec2(0, 0));
    SetNextWindowSize(ImVec2(width, height));
    SetNextWindowSizeConstraints(ImVec2(width, height), ImVec2(width, height));

    Begin(text);
}

void ImGuiManager::AddText(const char* text)
{
    Text(text);
}

void ImGuiManager::AddSliderInt(const char* text, int *value, int start, int end)
{
    SliderInt(text, value, start, end);
}

void ImGuiManager::AddSliderFloat(const char* text, float* value, float start, float end)
{
    SliderFloat(text, value, start, end);
}

void ImGuiManager::AddColorPicker(const char* text, float* value)
{
    ColorPicker3(text, (float*)&value);
}

void ImGuiManager::AddCheckbox(const char* text, bool* value)
{
    Checkbox(text, value);
}

void ImGuiManager::AddSameLine()
{
    SameLine();
}

void ImGuiManager::FinishWindow()
{
    End();
    Render();
}

void ImGuiManager::RenderWindow()
{
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}
