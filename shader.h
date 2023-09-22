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
    void use() const;
    void setInt(const std::string &name, int value) const;
private:
    GLuint programID;

    static void checkCompileErrors(unsigned int shader, const std::string& type);
};


#endif //CUBELANDS_SHADER_H
