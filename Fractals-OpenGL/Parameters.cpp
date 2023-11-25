#include "Parameters.h"

GLint WIDTH = 1080;
GLint HEIGHT = 720;
extern int CONF_WIDTH = 250;
extern int CONF_HEIGHT = 100;

int ITERATIONS = 50;
const int MAX_ITERATIONS = 100;

vec2 CONSTANT{ 0, 0 };
extern const float MAX_CONSTANT = 1.5;
extern const float MIN_CONSTANT = -1.5;

extern int ZOOM = 0;
float ZOOM_SPEED = 1.1f;

const char* MAIN_WINDOW_NAME = "Fractals";
const char* CONF_WINDOW_NAME = "Configuration";

float MOVE_SPEED = 1.0f;
float* COLOR = new float[3]{ 1.0f, 1.0f, 1.0f};
