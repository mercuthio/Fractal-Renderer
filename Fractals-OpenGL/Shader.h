#pragma once

#include <iostream>
#include <fstream>

#include <GL\glew.h>

using namespace std;

class Shader
{
public:
	Shader();
	~Shader();

	void CreateFromFiles(const char* vShader, const char* fShader);
	GLuint GetProjectionLocation();
	GLuint GetModelLocation();

	void UpdateParameters();
	void UseShader();
	void UseVAO();
	void ClearShader();

private:
	GLuint shaderID, uniformProjection, uniformModel, VAO, VBO;

	void LoadShaderFromFile(const char*& filename, char*& result);
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void CreateVertex();
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	bool CheckResult(const char* text, GLuint id, int flag);
};

