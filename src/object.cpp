//
// Created by bmneu on 9/22/2023.
//

#include "object.h"

#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>

Object::Object(std::shared_ptr<Texture> texture, glm::vec3 pos, glm::mat4 rot, glm::vec3 scale) {
    this->texture = texture;
    this->pos = pos;
    this->rot = rot;
    this->scale = scale;
    updateModel();
    shouldUpdate = false;

    float vertices[] = {
            // Back face
            -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,

            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

            // Left face
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            // Right face
            0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f, 0.0f,

            // Bottom face
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            // Top face
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

glm::mat4 Object::getModel() {
    if (shouldUpdate) {
        updateModel();
    }
    return model;
}

void Object::setPos(glm::vec3 pos) {
    this->pos = pos;
    shouldUpdate = true;
}

void Object::setX(float x) {
    pos.x = x;
    shouldUpdate = true;
}

void Object::setY(float y) {
    pos.y = y;
    shouldUpdate = true;
}

void Object::setZ(float z) {
    pos.z = z;
    shouldUpdate = true;
}

void Object::setRot(glm::mat4 rot) {
    this->rot = rot;
    shouldUpdate = true;
}

void Object::setScale(float scale) {
    this->scale = glm::vec3(scale);
    shouldUpdate = true;
}

void Object::updateModel() {
    glm::mat4 model(1.0f);
    model = glm::translate(model, pos);
    model = model * rot;
    model = glm::scale(model, scale);
    this->model = model;
}

std::shared_ptr<Texture> Object::getTexture() {
    return texture;
}
