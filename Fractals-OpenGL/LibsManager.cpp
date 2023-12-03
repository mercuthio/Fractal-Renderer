#include "LibsManager.h"

LibsManager::LibsManager()
{
    m_mainWindow = nullptr;
    m_imGuiManager = nullptr;
    m_fps = 0;
}

void LibsManager::Initialize()
{
    try
    {
        InitGLFW();
        InitOpenGL();
        InitialiseWindow(WIDTH, HEIGHT, MAIN_WINDOW_NAME);

        int bufferWidth, bufferHeight;
        glfwGetFramebufferSize(m_mainWindow, &bufferWidth, &bufferHeight);
        glfwMakeContextCurrent(m_mainWindow);

        InitGLEW();

        glViewport(0, 0, bufferWidth, bufferHeight);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, WIDTH, 0.0, HEIGHT, -1.0, 1.0);

        m_imGuiManager = new ImGuiManager();
        m_imGuiManager->Initialize(m_mainWindow);
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

void LibsManager::InitOpenGL()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void LibsManager::InitialiseWindow(const int width, const int height, const char* windowName)
{
    m_mainWindow = glfwCreateWindow(width, height, windowName, NULL, NULL);
    if (!m_mainWindow)
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
        glfwDestroyWindow(m_mainWindow);
        glfwTerminate();
        throw exception("GLEW initialisation failed");
    }
}

void LibsManager::AddVec2Slider(const char* text, vec2* value, float start, float end)
{
    m_imGuiManager->AddSliderFloat(text, &value->x, start, end);
    value->y = value->x;
}

void LibsManager::AddRestartZoomButton(const char* text)
{
    if (AddButton(text))
    {
        SCALE = 1;
    }
}

double LibsManager::GetFPS()
{
    UpdateFPS();
    return m_fps;
}

void LibsManager::UpdateFPS()
{
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - m_lastTime;
    m_frameCount++;

    if (deltaTime >= 1.0) 
    {
        m_fps = m_frameCount / deltaTime;

        m_frameCount = 0;
        m_lastTime = currentTime;
    }
}
