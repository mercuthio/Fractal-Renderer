#include "Shader.h"
#include "Parameters.h"

Shader::Shader() 
{
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
    VAO = 0;
    VBO = 0;
}


Shader::~Shader()
{
    ClearShader();
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

GLuint Shader::GetProjectionLocation()
{
    return uniformProjection;
}
GLuint Shader::GetModelLocation()
{
    return uniformModel;
}

void Shader::UpdateParameters()
{
    glUseProgram(shaderID);
    glUniform2f(glGetUniformLocation(shaderID, "resolution"), (float)WIDTH, (float)HEIGHT);

    glUniform1i(glGetUniformLocation(shaderID, "maxIterations"), ITERATIONS);

    glUniform1f(glGetUniformLocation(shaderID, "scale"), SCALE);

    glUniform2f(glGetUniformLocation(shaderID, "constant"), (float)CONSTANT.x, (float)CONSTANT.y);

    glUniform2f(glGetUniformLocation(shaderID, "focalPoint"), (float)FOCAL_POINT.x, (float)FOCAL_POINT.y);
}

void Shader::UseShader()
{
    glUseProgram(shaderID);
}

void Shader::UseVAO()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


void Shader::ClearShader()
{
    if (shaderID != 0)
    {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }

    uniformModel = 0;
    uniformProjection = 0;
}


void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
    shaderID = glCreateProgram();

    if (!shaderID)
    {
        printf("Error creating shader program!\n");
        return;
    }

    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }

    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformModel = glGetUniformLocation(shaderID, "model");
}


void Shader::CreateVertex()
{
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Configuración de uniformes
    glUseProgram(shaderID);
    glUniform2f(glGetUniformLocation(shaderID, "resolution"), (float)WIDTH, (float)HEIGHT);
    glUniform2f(glGetUniformLocation(shaderID, "viewPort"), 3.0f, 3.0f);
    glUniform1i(glGetUniformLocation(shaderID, "maxIterations"), ITERATIONS);
    glUniform1f(glGetUniformLocation(shaderID, "scale"), 1);
    glUniform2f(glGetUniformLocation(shaderID, "constant"), (float)CONSTANT.x, (float)CONSTANT.y);
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
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        cout << "ERROR: " << text << " " << eLog << endl;
    }
    return result;
}
