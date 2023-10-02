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
    Object(std::shared_ptr<Texture> texture, glm::vec3 pos = glm::vec3(0, 0, 0), glm::mat4 rot = glm::mat4(1.0f), glm::vec3 scale = glm::vec3(1.0f));

    glm::mat4 getModel();
    std::shared_ptr<Texture> getTexture();

    void setPos(glm::vec3 pos);
    void setX(float x);
    void setY(float y);
    void setZ(float z);

    void setRot(glm::mat4 rot);

    void setScale(float scale);

    int getVertCount();

private:
    void updateModel();

    std::shared_ptr<Texture> texture;
    glm::mat4 model;
    glm::vec3 pos;
    glm::mat4 rot;
    glm::vec3 scale;

    int vertCount;
    bool shouldUpdate;
};


#endif //CUBELANDS_OBJECT_H
