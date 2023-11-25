#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string.h>

#include "ShaderManager.h"

using namespace std;
using namespace glm;

extern GLint WIDTH;
extern GLint HEIGHT;
extern int CONF_WIDTH;
extern int CONF_HEIGHT;

extern int ITERATIONS;
extern const int MAX_ITERATIONS;

extern vec2 CONSTANT;
extern const float MAX_CONSTANT;
extern const float MIN_CONSTANT;

extern int ZOOM;
extern float ZOOM_SPEED;

extern const char* MAIN_WINDOW_NAME;
extern const char* CONF_WINDOW_NAME;

extern float MOVE_SPEED;
extern float* COLOR;

extern GLuint VAO, VBO, shader;
