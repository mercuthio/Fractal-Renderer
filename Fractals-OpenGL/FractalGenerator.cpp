#include "FractalGenerator.h"

FractalGenerator::FractalGenerator() {}

void FractalGenerator::Display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);

	UpdateZoom();
	GenerateFractal();

	glEnd();
	glFlush();
}

void FractalGenerator::Move(Movement type)
{
	switch (type)
	{
	case Movement::UP:
		focalPoint.y += MOVE_SPEED;
		break;
	case Movement::LEFT:
		focalPoint.x -= MOVE_SPEED;
		break;
	case Movement::RIGHT:
		focalPoint.x += MOVE_SPEED;
		break;
	case Movement::DOWN:
		focalPoint.y -= MOVE_SPEED;
		break;
	}
}

void FractalGenerator::SetIterations(int iter)
{
	ITERATIONS = iter;
}

void FractalGenerator::UpdateZoom()
{
	switch (ZOOM)
	{
	case 1:
		scale *= ZOOM_SPEED;
		break;
	case -1:
		scale /= ZOOM_SPEED;
		break;
	}
}

void FractalGenerator::GenerateFractal()
{
	vec2 vec{ 0, 0 };
	float iter = 0, color = 0;

	for (GLfloat y = 0; y < HEIGHT; ++y)
	{
		for (GLfloat x = 0; x < WIDTH; ++x)
		{
			vec.x = ((x - WIDTH / 2) / scale + focalPoint.x) * 4 / WIDTH;
			vec.y = ((y - HEIGHT / 2) / scale + focalPoint.y) * 4 / HEIGHT;

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
	//vec2 vec{ 0,0 };
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
