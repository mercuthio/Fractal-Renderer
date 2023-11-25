#include "LibsManager.h"
#include "FractalGenerator.h"

FractalGenerator fractal;

void Reshape(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);

    WIDTH = width;
    HEIGHT = height;

    fractal.Display();
}

void ProcessKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            fractal.Move(Movement::UP);
            break;
        case GLFW_KEY_DOWN:
            fractal.Move(Movement::DOWN);
            break;
        case GLFW_KEY_LEFT:
            fractal.Move(Movement::LEFT);
            break;
        case GLFW_KEY_RIGHT:
            fractal.Move(Movement::RIGHT);
            break;
        }
    }
}

int main()
{
    LibsManager libsManager;
    libsManager.Initialize();
    libsManager.SetResizeCallBack(Reshape);
    libsManager.SetKeyCallBack(ProcessKey);

    while (!libsManager.GetWindowShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        libsManager.StartGUI();
        libsManager.AddIntSlider("Iterations", &ITERATIONS, 0, MAX_ITERATIONS);
        libsManager.AddVec2Slider("Constant", &CONSTANT, MIN_CONSTANT, MAX_CONSTANT);
        libsManager.AddIntSlider("Zoom", &ZOOM, -1, 1);
        libsManager.FinishGUI();

        fractal.Display();

        libsManager.RenderGUI();
        libsManager.SwapBuffers();

        glfwPollEvents();
    }

    glfwTerminate();

    libsManager.SwapBuffers();
    return 0;
}
