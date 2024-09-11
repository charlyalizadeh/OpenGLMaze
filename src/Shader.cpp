#include "../include/Shader.hpp"


unsigned int compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex": "fragment") << " shader!\n";
        std::cout << message << "\n";
        std::cout << source << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

Shader::Shader() {}

Shader::Shader(const std::string& filepath) {
    init(filepath);
}

Shader::~Shader() {
    glDeleteProgram(m_shaderProgramId);
}

ShaderProgramSource Shader::parseShader() {
    std::ifstream stream(filepath);

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

void Shader::createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource) {
    m_shaderProgramId = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(m_shaderProgramId, vs);
    glAttachShader(m_shaderProgramId, fs);
    glLinkProgram(m_shaderProgramId);
    glValidateProgram(m_shaderProgramId);
}

void Shader::init(const std::string& filepath) {
    this->filepath = filepath;
    ShaderProgramSource source = parseShader();
    createShaderProgram(source.vertexSource, source.fragmentSource);
    glUseProgram(m_shaderProgramId);
}

void Shader::bind() const {
    glUseProgram(m_shaderProgramId);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::setUniformIntArray(const std::string& name, int* values, int count) {
    unsigned int location = glGetUniformLocation(m_shaderProgramId, name.c_str());
    if(location == -1)
    {
        std::cout << name << " not found or not used.\n";
        return;
    }
    glUniform1iv(location, count, values);
}
