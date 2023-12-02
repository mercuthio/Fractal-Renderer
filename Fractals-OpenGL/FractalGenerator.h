#pragma once

#include "Parameters.h"
#include "Shader.h"

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
	FractalGenerator(const char* vShaderFile, const char* fShaderFile);
	~FractalGenerator();

	void Display();
	void DisplayFromShader();

	void Move(Movement type);
	void SetIterations(int iter);

private:
	Shader* fractalShader;

	void UpdateConstant();
	void UpdateZoom();
	void GenerateFractal();
	float CalculateIteration(vec2 vec);
	vec2 GetNextIteration(vec2 vec);
};

