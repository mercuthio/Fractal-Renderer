#include "Shader.h"
#include "Parameters.h"

Shader::Shader() 
{
    m_shaderID = 0;
    m_uniformModel = 0;
    m_uniformProjection = 0;
    m_VAO = 0;
    m_VBO = 0;
    rangesBuffer = 0;
    rangesTotalBuffer = 0;
    colorBuffer = 0;
}

void Shader::LoadShaderFromFile(const char*& filename, char*& result)
{
    ifstream file(filename, ios::ate | ios::binary);;

    if (!file.is_open())
    {
        cout << "ERROR: Cant open the file " << filename << endl;
        return;
    }

    streampos size = file.tellg();
    file.seekg(0, ios::beg);

    result = new char[static_cast<size_t>(size) + 1];

    file.read(result, size);

    result[size] = '\0';

    file.close();
}

void Shader::CreateFromFiles(const char* vShader, const char* fShader)
{
    char* vShaderCode = nullptr;
    char* fShaderCode = nullptr;

    LoadShaderFromFile(vShader, vShaderCode);
    LoadShaderFromFile(fShader, fShaderCode);

    CompileShader(vShaderCode, fShaderCode);
    CreateVertex();
}

void Shader::UpdateParameters()
{
    glUseProgram(m_shaderID);    

    glBindBuffer(GL_UNIFORM_BUFFER, rangesBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, RANGES.size() * sizeof(float), RANGES.data());

    glBindBuffer(GL_UNIFORM_BUFFER, colorBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, COLORS.size() * sizeof(vec3), COLORS.data());

    glUniform2f(glGetUniformLocation(m_shaderID, "resolution"), (float)WIDTH, (float)HEIGHT);

    glUniform1i(glGetUniformLocation(m_shaderID, "iterations"), ITERATIONS);

    glUniform1f(glGetUniformLocation(m_shaderID, "scale"), SCALE);

    glUniform2f(glGetUniformLocation(m_shaderID, "constant"), (float)CONSTANT.x, (float)CONSTANT.y);

    glUniform2f(glGetUniformLocation(m_shaderID, "focalPoint"), (float)FOCAL_POINT.x, (float)FOCAL_POINT.y);
}

void Shader::UseVAO()
{
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


void Shader::ClearShader()
{
    if (m_shaderID != 0)
    {
        glDeleteProgram(m_shaderID);
        m_shaderID = 0;
    }

    m_uniformModel = 0;
    m_uniformProjection = 0;
}


void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
    m_shaderID = glCreateProgram();

    if (!m_shaderID)
    {
        printf("Error creating shader program!\n");
        return;
    }

    AddShader(m_shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(m_shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(m_shaderID);
    glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }

    glValidateProgram(m_shaderID);
    glGetProgramiv(m_shaderID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }

    m_uniformProjection = glGetUniformLocation(m_shaderID, "projection");
    m_uniformModel = glGetUniformLocation(m_shaderID, "model");
}


void Shader::CreateVertex()
{
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(m_shaderID);

    glGenBuffers(1, &rangesBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, rangesBuffer);
    glBufferData(GL_UNIFORM_BUFFER, 5 * sizeof(float), RANGES.data(), GL_STATIC_DRAW);

    glUniformBlockBinding(m_shaderID, glGetUniformBlockIndex(m_shaderID, "rangesBlock"), 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, rangesBuffer);

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, colorBuffer);
    glBufferData(GL_UNIFORM_BUFFER, 5 * sizeof(vec3), COLORS.data(), GL_STATIC_DRAW);

    glUniformBlockBinding(m_shaderID, glGetUniformBlockIndex(m_shaderID, "colorsBlock"), 1);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, colorBuffer);

    glUniform2f(glGetUniformLocation(m_shaderID, "resolution"), (float)WIDTH, (float)HEIGHT);
    glUniform2f(glGetUniformLocation(m_shaderID, "viewPort"), 3.0f, 3.0f);
    glUniform1i(glGetUniformLocation(m_shaderID, "iterations"), ITERATIONS);
    glUniform1f(glGetUniformLocation(m_shaderID, "scale"), 1);
    glUniform2f(glGetUniformLocation(m_shaderID, "constant"), (float)CONSTANT.x, (float)CONSTANT.y);
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = (GLint)strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, 1024, NULL, eLog);
        fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
        return;
    }

    glAttachShader(theProgram, theShader);
}

bool Shader::CheckResult(const char* text, GLuint id, int flag)
{
    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetProgramiv(id, flag, &result);
    if (!result)
    {
        glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
        cout << "ERROR: " << text << " " << eLog << endl;
    }
    return result;
}
