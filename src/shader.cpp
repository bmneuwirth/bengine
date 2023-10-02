#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // load the vertex shader and the fragment shader
    std::ifstream vShaderFile(vertexPath);
    if (!vShaderFile.is_open()) {
        throw std::invalid_argument("Could not open the vertex file");
    }
    std::string vertexStr((std::istreambuf_iterator<char>(vShaderFile)),
                           std::istreambuf_iterator<char>());
    if (vShaderFile.bad()) {
        throw std::invalid_argument("Problem while reading vertex file");
    }

    std::ifstream fShaderFile(fragmentPath);
    if (!fShaderFile.is_open()) {
        throw std::invalid_argument("Could not open the fragment file");
    }
    std::string fragmentStr((std::istreambuf_iterator<char>(fShaderFile)),
                             std::istreambuf_iterator<char>());
    if (fShaderFile.bad()) {
        throw std::invalid_argument("Problem while reading fragment file");
    }

    unsigned int vertexShader, fragmentShader;
    const char* vShaderCode = vertexStr.c_str();
    const char* fShaderCode = fragmentStr.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);
    checkCompileErrors(programID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(programID);
}

void Shader::use() const {
    glUseProgram(programID);
}

void Shader::checkCompileErrors(unsigned int shader, const std::string& type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::setMat4(const std::string &name, const float* value) const {
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, value);
}
