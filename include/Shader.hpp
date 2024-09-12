#ifndef SHADER_H
#define SHADER_H

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "Dimension.hpp"

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


enum class ShaderType {
    NONE = -1, VERTEX = 0, FRAGMENT = 1
};

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

unsigned int compileShader(unsigned int type, const std::string& source);

class Shader {
public:
    Shader();
    Shader(const std::string& filepath);
    ~Shader();

    ShaderProgramSource parseShader();
    void createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
    void init(const std::string& filepath);

    void bind() const;
    void unbind() const;

    void setUniformIntArray(const std::string& name, int* values, int count);

private:
    unsigned int m_shaderProgramId;
    std::string filepath;
};


#endif
