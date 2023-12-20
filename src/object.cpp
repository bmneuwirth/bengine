//
// Created by bmneu on 9/22/2023.
//

#include "object.h"

#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>
#include <utility>

const int FLOATS_PER_VERTEX = 5;

Object::Object(const float* vertices, size_t vertexArraySize, std::shared_ptr<Texture> texture, glm::vec3 pos, glm::mat4 rot, glm::vec3 scale) {
    this->texture = std::move(texture);
    this->pos = pos;
    this->rot = rot;
    this->scale = scale;
    updateModel();
    shouldUpdate = false;

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexArraySize, vertices, GL_STATIC_DRAW);

    vertCount = vertexArraySize / FLOATS_PER_VERTEX;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(float), (void*)nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(float), (void*)(3 * sizeof(float)));

    // Unbind the current VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

int Object::getVertCount() {
    return vertCount;
}

unsigned int Object::getVBO() {
    return VBO;
}
