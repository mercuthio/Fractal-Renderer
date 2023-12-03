#include "Parameters.h"

GLint WIDTH = 1080;
GLint HEIGHT = 720;
extern int CONF_WIDTH = 270;
extern int CONF_HEIGHT = 140;

int ITERATIONS = 300;
const int MAX_ITERATIONS = 600;

vec2 CONSTANT{ 0, 0.646f };
bool INCREASE_CONSTANT_X = false;
bool INCREASE_CONSTANT_Y = false;
float CONSTANT_INCREASE = 0.04f;
extern const float MAX_CONSTANT = 1.5f;
extern const float MIN_CONSTANT = -1.5f;

vec2 FOCAL_POINT{ 0,0 };

extern int ZOOM = 0;
float ZOOM_SPEED = 0.2f;
float SCALE = 1;
float MIN_SCALE = 0.0001f;

const char* MAIN_WINDOW_NAME = "Fractals";
const char* CONF_WINDOW_NAME = "Configuration";

float MOVE_SPEED = 1.3f;
float* COLOR = new float[3]{ 1.0f, 1.0f, 1.0f};
vector<int> RANGES;
vector<vec3> COLORS;
vector<int> RANGES_TOTALS{0};
