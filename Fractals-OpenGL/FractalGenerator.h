#pragma once

#include "Parameters.h"

enum class Movement
{
	UP,
	LEFT,
	RIGHT,
	DOWN
};

class FractalGenerator
{
public:
	FractalGenerator();
	void Display();

	void Move(Movement type);
	void SetIterations(int iter);

private:

	float scale = 1;
	vec2 focalPoint{ 0,0 };

	void UpdateZoom();
	void GenerateFractal();
	float CalculateIteration(vec2 vec);
	vec2 GetNextIteration(vec2 vec);
};

