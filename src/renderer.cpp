//
// Created by Ben Neuwirth on 9/30/23.
//

#include "renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <utility>

Renderer::Renderer() {
    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // position attribute
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void Renderer::startDraw() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    curShader->setMat4("view", glm::value_ptr(camera->getViewMatrix()));
}

void Renderer::draw(const std::shared_ptr<Object>& obj) {
    curShader->setMat4("model", glm::value_ptr(obj->getModel()));
    obj->getTexture()->bind();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, obj->getVertCount());
}

void Renderer::setCamera(std::shared_ptr<Camera> cam) {
    camera = std::move(cam);
}

void Renderer::setShader(std::shared_ptr<Shader> shader) {
    curShader = std::move(shader);
    curShader->use();
    curShader->setMat4("projection", glm::value_ptr(camera->getProjMatrix()));
}
