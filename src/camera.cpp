//
// Created by Ben Neuwirth on 9/30/23.
//

#include "camera.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

const float SPEED = 2.0f;
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SENSITIVITY =  0.1f;

Camera::Camera(glm::vec3 pos, glm::vec3 up) {
    this->pos = pos;
    this->worldUp = up;
    this->yaw = YAW;
    this->pitch = PITCH;
    updateDir();
}

void Camera::processMovement(float dt, float forwardAmt, float rightAmt) {
    float vel = SPEED * dt;
    pos += front * vel * forwardAmt;
    pos += right * vel * rightAmt;
}

glm::mat4 Camera::getViewMatrix() {
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, -pos);
    return view;
}

void Camera::updateDir() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(front, right));
}