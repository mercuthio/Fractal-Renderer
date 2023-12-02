#include "Parameters.h"

bool GPU_ENABLED = true;

GLint WIDTH = 1080;
GLint HEIGHT = 720;
extern int CONF_WIDTH = 275;
extern int CONF_HEIGHT = 150;

int ITERATIONS = 50;
const int MAX_ITERATIONS = 1000;

vec2 CONSTANT{ 0, 0 };
bool INCREASE_CONSTANT_X = false;
bool INCREASE_CONSTANT_Y = false;
float CONSTANT_INCREASE = 0.0003;
extern const float MAX_CONSTANT = 1.5;
extern const float MIN_CONSTANT = -1.5;

vec2 FOCAL_POINT{ 0,0 };

extern int ZOOM = 0;
float ZOOM_SPEED = 1.001f;
float SCALE = 1;

const char* MAIN_WINDOW_NAME = "Fractals";
const char* CONF_WINDOW_NAME = "Configuration";

float MOVE_SPEED = 0.8f;
float* COLOR = new float[3]{ 1.0f, 1.0f, 1.0f};
