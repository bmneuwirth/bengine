//
// Created by Ben Neuwirth on 9/30/23.
//

#ifndef CUBELANDS_RENDERER_H
#define CUBELANDS_RENDERER_H

#include <memory>
#include <GL/glew.h>
#include "object.h"
#include "camera.h"
#include "shader.h"

class Renderer {
public:
    Renderer();

    void startDraw();
    void draw(const std::shared_ptr<Object>& obj);
    void setCamera(std::shared_ptr<Camera> cam);
    void setShader(std::shared_ptr<Shader> shader);

private:
    GLuint VAO;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Shader> curShader;
};


#endif //CUBELANDS_RENDERER_H
