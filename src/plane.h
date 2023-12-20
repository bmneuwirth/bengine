#pragma once
#include "object.h"

class Plane : public Object {

public:
    explicit Plane(std::shared_ptr<Texture> texture, glm::vec3 pos = glm::vec3(0, 0, 0), glm::mat4 rot = glm::mat4(1.0f), glm::vec3 scale = glm::vec3(1.0f)) : Object(&vertices[0], sizeof(vertices), texture, pos, rot, scale) {

    }

private:
    static constexpr const float vertices[] = {
        -0.5f,  0.0f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.f, -0.5f,  0.0f, 1.0f
    };

};