#include "ShaderManager.h"

ShaderManager::ShaderManager() {}

void ShaderManager::LoadShaderFromFile(const char*& filename, char*& result)
{
    ifstream file(filename, ios::ate | ios::binary);;

    if (!file.is_open())
    {
        cout << "ERROR: al abrir el fichero " << filename << endl;
        return;
    }

    streampos size = file.tellg();
    file.seekg(0, ios::beg);

    result = new char[static_cast<size_t>(size) + 1];

    file.read(result, size);

    result[size] = '\0';

    file.close();
}
