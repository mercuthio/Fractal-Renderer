#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string.h>

#include "Shader.h"
#include <vector>

using namespace std;
using namespace glm;

extern GLint WIDTH;
extern GLint HEIGHT;
extern int CONF_WIDTH;
extern int CONF_HEIGHT;

extern int ITERATIONS;
extern const int MAX_ITERATIONS;

extern vec2 CONSTANT;
extern bool INCREASE_CONSTANT_X;
extern bool INCREASE_CONSTANT_Y;
extern float CONSTANT_INCREASE;
extern const float MAX_CONSTANT;
extern const float MIN_CONSTANT;

extern vec2 FOCAL_POINT;

extern int ZOOM;
extern float ZOOM_SPEED;
extern float SCALE;
extern float MIN_SCALE;

extern const char* MAIN_WINDOW_NAME;
extern const char* CONF_WINDOW_NAME;

extern float MOVE_SPEED;
extern float* COLOR;
extern vector<int> RANGES;
extern vector<vec3> COLORS;
extern vector<int> RANGES_TOTALS;

extern GLuint VAO, VBO, shader;
