#include <Crunch/core/renderer/Shader.hpp>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace Crunch {

char* Shader::load(const char* path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return NULL;

    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    char* buffer = new char[size + 1];

    if (file.read(buffer, size)) {
        buffer[size] = '\0';
        tsrc = buffer;
        return buffer;
    }

    delete [] buffer;
    return nullptr;
}

uint32_t Shader::createShader(GLenum type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    return shader;
}

};
