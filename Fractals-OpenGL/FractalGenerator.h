#pragma once

#include "Parameters.h"
#include "Shader.h"
#include <vector>

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

	void AddColor(int end, const vec3& rgb);
	void Move(Movement type);
	void SaveFractalToFile(const char* name);
	void LoadFractalFromFile(const char* name);

private:
	Shader* m_fractalShader;
	float m_lastTime, m_deltaTime;

	void UpdateParameters();
	void UpdateDeltaTime();
	void UpdateConstant();
	void UpdateZoom();

	void GenerateFractal();
	float CalculateIteration(vec2 vec);
	vec2 GetNextIteration(vec2 vec);
};

