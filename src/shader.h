#ifndef CUBELANDS_SHADER_H
#define CUBELANDS_SHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

/**
 * A class representing a shader program used by OpenGL for rendering.
 * The vertex and fragment shaders are loaded at creation and compiled into a shader program.
 */
class Shader {
public:
    /**
     * Creates a shader program with a given vertex and fragment shader.
     * @param vertexPath the path to the vertex shader to use
     * @param fragmentPath the path to the fragment shader to use
     */
    Shader(const char* vertexPath, const char* fragmentPath);

    /**
     * Deletes the shader program.
     */
    ~Shader();
    Shader(const Shader& other) = delete;
    Shader& operator=(const Shader& other) = delete;

    // TODO: Add move operators?

    /**
     * Uses this shader program when rendering
     */
    void use() const;

    /**
     * Set a uniform int value for this shader program
     * @param name the name of the uniform to set
     * @param value the value to set the uniform to
     */
    void setInt(const std::string &name, int value) const;

    /**
     * Sets a uniform mat4 value for this shader program
     * @param name the name of the uniform to set
     * @param value the value to set the uniform to
     */
    void setMat4(const std::string &name, const float* value) const;

private:
    GLuint programID;

    /**
     * Logs shader compile errors to the standard output stream
     * @param shader the shader to log errors for
     * @param type the type of shader ("VERTEX", "FRAGMENT", or "PROGRAM")
     */
    static void checkCompileErrors(unsigned int shader, const std::string& type);
};


#endif //CUBELANDS_SHADER_H
