#include "FractalGenerator.h"

FractalGenerator::FractalGenerator() 
{
	m_fractalShader = nullptr;
	m_lastTime = 0;
	m_deltaTime = 0;
}

FractalGenerator::FractalGenerator(const char* vShaderFile, const char* fShaderFile)
{
	m_fractalShader = new Shader();
	m_fractalShader->CreateFromFiles(vShaderFile, fShaderFile);
	m_lastTime = 0;
	m_deltaTime = 0;
}

FractalGenerator::~FractalGenerator()
{
	delete m_fractalShader;
}

void FractalGenerator::Display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);

	UpdateParameters();
	GenerateFractal();

	glEnd();
	glFlush();
}

void FractalGenerator::DisplayFromShader()
{
	if (m_fractalShader == nullptr)
	{
		cout << "ERROR: FractalShader not initialized" << endl;
		return;
	}

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	UpdateParameters();
	m_fractalShader->UpdateParameters();
	m_fractalShader->UseVAO();	
}

void FractalGenerator::UpdateParameters()
{
	UpdateDeltaTime();
	UpdateConstant();
	UpdateZoom();
}

void FractalGenerator::UpdateDeltaTime()
{
	float now = (float)glfwGetTime();
	m_deltaTime = now - m_lastTime;
	m_lastTime = now;
}

void FractalGenerator::UpdateConstant()
{
	float constantChange = CONSTANT_INCREASE * m_deltaTime;

	if (INCREASE_CONSTANT_X &&
		CONSTANT.x + CONSTANT_INCREASE < MAX_CONSTANT)
	{
		CONSTANT.x += constantChange;
	}

	if (INCREASE_CONSTANT_Y &&
		CONSTANT.y + CONSTANT_INCREASE < MAX_CONSTANT)
	{
		CONSTANT.y += constantChange;
	}
}

void FractalGenerator::UpdateZoom()
{
	float zoomChange = (float)pow(2, ZOOM_SPEED * m_deltaTime);

	switch (ZOOM)
	{
	case 1:
		SCALE *= zoomChange;
		MOVE_SPEED /= zoomChange;
		break;
	case -1:
		SCALE /= zoomChange;
		MOVE_SPEED *= zoomChange;
		break;
	}

	SCALE = std::max(SCALE, MIN_SCALE);
}

void FractalGenerator::AddColor(float end, const vec3& rgb)
{
	RANGES.push_back(end * MAX_ITERATIONS);
	COLORS.push_back(rgb);
}

void FractalGenerator::Move(Movement type)
{
	switch (type)
	{
	case Movement::UP:
		FOCAL_POINT.y += MOVE_SPEED;
		break;
	case Movement::LEFT:
		FOCAL_POINT.x -= MOVE_SPEED;
		break;
	case Movement::RIGHT:
		FOCAL_POINT.x += MOVE_SPEED;
		break;
	case Movement::DOWN:
		FOCAL_POINT.y -= MOVE_SPEED;
		break;
	}
}

void FractalGenerator::SaveFractalToFile(const char* name)
{
	std::ofstream archivo(name);

	if (!archivo.is_open()) {
		cout << "Error al abrir el archivo para escritura." << endl;
		return;
	}

	archivo << ITERATIONS << '\n';
	archivo << CONSTANT.x << '\n';
	archivo << CONSTANT.y << '\n';

	archivo.close();
}

void FractalGenerator::LoadFractalFromFile(const char* name)
{
	std::ifstream archivo(name);

	if (!archivo.is_open()) {
		cout << "Error al abrir el archivo para lectura." << endl;
	}

	archivo >> ITERATIONS;
	archivo >> CONSTANT.x;
	archivo >> CONSTANT.y;

	archivo.close();
}

void FractalGenerator::GenerateFractal()
{
	vec2 vec{ 0, 0 };
	float iter = 0, color = 0;

	for (GLfloat y = 0; y < HEIGHT; ++y)
	{
		for (GLfloat x = 0; x < WIDTH; ++x)
		{
			vec.x = ((x - WIDTH / 2) / SCALE + FOCAL_POINT.x) * 4 / WIDTH;
			vec.y = ((y - HEIGHT / 2) / SCALE + FOCAL_POINT.y) * 4 / HEIGHT;

			iter = CalculateIteration(vec);
			color = iter / ITERATIONS;

			glColor3f(color * COLOR[0], color * COLOR[1], color * COLOR[2]);
			glVertex2f(x, y);
		}
	}
}

float FractalGenerator::CalculateIteration(vec2 vec)
{
	float iter = 0.0;
	while (length(vec) < 4.0 && iter < ITERATIONS)
	{
		vec = GetNextIteration(vec);
		iter++;
	}

	const float mod = sqrt(length(vec));
	const float smooth_it = float(iter) - log2(std::max(1.0f, log2(mod)));

	return smooth_it;
}

vec2 FractalGenerator::GetNextIteration(vec2 vec)
{
	const double zr = vec.x * vec.x - vec.y * vec.y;
	const double zi = 2.0 * vec.x * vec.y;

	return vec2{zr, zi} + CONSTANT;
}
