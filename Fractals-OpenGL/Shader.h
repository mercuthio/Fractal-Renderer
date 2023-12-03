#pragma once

#include <iostream>
#include <fstream>

#include <GL\glew.h>

using namespace std;

class Shader
{
public:
	Shader();
	~Shader() { ClearShader(); }

	void CreateFromFiles(const char* vShader, const char* fShader);

	void UpdateParameters();
	void UseShader() { glUseProgram(m_shaderID); }
	void UseVAO();
	void ClearShader();

private:
	GLuint m_shaderID, m_uniformProjection, m_uniformModel, m_VAO, m_VBO, m_bufferObjRanges, m_bufferTextRanges, m_bufferObjColors, m_bufferTextColors, m_bufferObjRangesTotal, m_bufferTextRangesTotal;

	void LoadShaderFromFile(const char*& filename, char*& result);
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void CreateVertex();
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	bool CheckResult(const char* text, GLuint id, int flag);
};

