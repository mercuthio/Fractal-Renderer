#pragma once

#include <iostream>
#include <fstream>

using namespace std;

class ShaderManager
{
public:
	ShaderManager();

	static void LoadShaderFromFile(const char*& filename, char*& result);
};

