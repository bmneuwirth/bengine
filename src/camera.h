//
// Created by Ben Neuwirth on 9/30/23.
//

#ifndef CUBELANDS_CAMERA_H
#define CUBELANDS_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera(glm::vec3 pos, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), bool flyMode = false);

    void processMovement(float dt, float forwardAmt, float rightAmt);
    void processMouse(float xOffset, float yOffset);
    glm::mat4 getViewMatrix();

private:
    void updateDir();

    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    bool flyMode;
};


#endif //CUBELANDS_CAMERA_H
