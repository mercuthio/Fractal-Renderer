#include "LibsManager.h"
#include "FractalGenerator.h"
#include <string>

FractalGenerator* fractal = nullptr;

double lastTime = 0.0f;

void Reshape(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);

    WIDTH = width;
    HEIGHT = height;

    fractal->Display();
}

void ProcessKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            fractal->Move(Movement::UP);
            break;
        case GLFW_KEY_DOWN:
            fractal->Move(Movement::DOWN);
            break;
        case GLFW_KEY_LEFT:
            fractal->Move(Movement::LEFT);
            break;
        case GLFW_KEY_RIGHT:
            fractal->Move(Movement::RIGHT);
            break;
        }
    }
}

int main()
{
    LibsManager* libsManager = new LibsManager();
    libsManager->Initialize();
    libsManager->SetResizeCallBack(Reshape);
    libsManager->SetKeyCallBack(ProcessKey);

    fractal = new FractalGenerator("shaders/vShader.sh", "shaders/fShader.sh");
    
    string strFps;

    while (!libsManager->GetWindowShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        strFps = "FPS: " + to_string(static_cast<int>(libsManager->GetFPS()));

        //GUI
        libsManager->StartGUI();

        libsManager->AddText(strFps.c_str());

        libsManager->AddIntSlider("Iterations", &ITERATIONS, 2, MAX_ITERATIONS);

        libsManager->AddFloatSlider("CX", &CONSTANT.x, MIN_CONSTANT, MAX_CONSTANT);
        libsManager->AddSameLine();
        libsManager->AddCheckBox("###Checkbox", &INCREASE_CONSTANT_X);

        libsManager->AddFloatSlider("CY", &CONSTANT.y, MIN_CONSTANT, MAX_CONSTANT);
        libsManager->AddSameLine();
        libsManager->AddCheckBox("###Checkbox2", &INCREASE_CONSTANT_Y);

        libsManager->AddIntSlider("Zoom", &ZOOM, -1, 1);
        libsManager->FinishGUI();

        fractal->DisplayFromShader();

        libsManager->RenderGUI();
        libsManager->SwapBuffers();

        glfwPollEvents();
    }

    delete fractal;
    delete libsManager;

    glfwTerminate();

    return 0;
}
