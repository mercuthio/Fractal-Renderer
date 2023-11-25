#include "LibsManager.h"

LibsManager::LibsManager()
{
    mainWindow = nullptr;
    imGuiManager = nullptr;
}

LibsManager::~LibsManager()
{
    delete imGuiManager;
}

void LibsManager::Initialize()
{
    try
    {
        InitGLFW();
        InitialiseWindow(WIDTH, HEIGHT, MAIN_WINDOW_NAME);

        int bufferWidth, bufferHeight;
        glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
        glfwMakeContextCurrent(mainWindow);

        InitGLEW();

        glViewport(0, 0, bufferWidth, bufferHeight);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, WIDTH, 0.0, HEIGHT, -1.0, 1.0);

        imGuiManager = new ImGuiManager();
        imGuiManager->Initialize(mainWindow);
    }
    catch (exception ex)
    {
        cout << "ERROR: " << ex.what() << endl;
    }
}

void LibsManager::InitGLFW()
{
    if (!glfwInit())
    {
        glfwTerminate();
        throw exception("GLFW initialisation failed");
    }
}

void LibsManager::InitialiseWindow(const int width, const int height, const char* windowName)
{
    mainWindow = glfwCreateWindow(width, height, windowName, NULL, NULL);
    if (!mainWindow)
    {
        glfwTerminate();
        throw exception("GLFW window creation failed");
    }
}

void LibsManager::InitGLEW()
{
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        throw exception("GLEW initialisation failed");
    }
}

bool LibsManager::GetWindowShouldClose()
{
    return glfwWindowShouldClose(mainWindow);
}

void LibsManager::SwapBuffers()
{
    glfwSwapBuffers(mainWindow);
}

void LibsManager::StartGUI()
{
    imGuiManager->StartWindow(CONF_WINDOW_NAME, (float)CONF_WIDTH, (float)CONF_HEIGHT);
}

void LibsManager::AddIntSlider(const char* text, int* value, int start, int end)
{
    imGuiManager->AddSliderInt(text, value, start, end);
}

void LibsManager::AddFloatSlider(const char* text, float* value, float start, float end)
{
    imGuiManager->AddSliderFloat(text, value, start, end);
}

void LibsManager::AddVec2Slider(const char* text, vec2* value, float start, float end)
{
    imGuiManager->AddSliderFloat(text, &value->x, start, end);
    value->y = value->x;
}

void LibsManager::AddColorPicker(const char* text, float* value)
{
    imGuiManager->AddColorPicker(text, value);
}

void LibsManager::FinishGUI()
{
    imGuiManager->FinishWindow();
}

void LibsManager::RenderGUI()
{
    imGuiManager->RenderWindow();
}