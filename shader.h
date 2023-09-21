#ifndef CUBELANDS_SHADER_H
#define CUBELANDS_SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    Shader(const Shader& other) = delete;
    Shader& operator=(const Shader& other) = delete;

    // TODO: Add move operators
    void use();
private:
    GLuint programID;

    void checkCompileErrors(unsigned int shader, std::string type);
};


#endif //CUBELANDS_SHADER_H
