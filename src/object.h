//
// Created by bmneu on 9/22/2023.
//

#ifndef CUBELANDS_OBJECT_H
#define CUBELANDS_OBJECT_H

#include <memory>
#include <glm/glm.hpp>
#include "texture.h"

class Object {
public:
    Object(std::shared_ptr<Texture> texture, glm::vec3 pos = glm::vec3(0, 0, 0), glm::mat4 rot = glm::mat4(1.0f));

    glm::mat4 getModel();

    void setPos(glm::vec3 pos);
    void setRot(glm::mat4 rot);

private:
    void updateModel();

    std::shared_ptr<Texture> texture;
    glm::mat4 model;
    glm::vec3 pos;
    glm::mat4 rot;

    bool shouldUpdate;
};


#endif //CUBELANDS_OBJECT_H
