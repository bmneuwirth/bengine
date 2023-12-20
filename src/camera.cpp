//
// Created by Ben Neuwirth on 9/30/23.
//

#include "camera.h"

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

const float SPEED = 5.0f;
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SENSITIVITY =  0.1f;
const float V_FOV = 45.0f;
const float Z_NEAR = 0.1f;
const float Z_FAR = 100.0f;
const bool CONSTRAIN_PITCH = true;

Camera::Camera(int screenWidth, int screenHeight, glm::vec3 pos, glm::vec3 up, bool flyMode) {
    proj = glm::perspective(glm::radians(V_FOV), (float)screenWidth/(float)screenHeight, Z_NEAR, Z_FAR);

    this->pos = pos;
    this->worldUp = up;
    this->yaw = YAW;
    this->pitch = PITCH;
    this->flyMode = flyMode;
    this->floorY = pos.y;
    updateDir();
}

void Camera::processMovement(float dt, float forwardAmt, float rightAmt) {
    float vel = SPEED * dt;
    if (flyMode) {
        pos += front * vel * forwardAmt;
    } else {
        glm::vec3 forward = glm::normalize(glm::cross(worldUp, right));
        pos += forward * vel * forwardAmt;
    }
    pos += right * vel * rightAmt;
}

void Camera::processMouse(float xOffset, float yOffset) {
    xOffset *= SENSITIVITY;
    yOffset *= SENSITIVITY;

    // Invert
    yaw += xOffset;
    pitch -= yOffset;

    if (CONSTRAIN_PITCH) {
        if (pitch > 89.0f) {
            pitch = 89.0f;
        } else if (pitch < -89.0f) {
            pitch = -89.0f;
        }
    }
    updateDir();
}

void Camera::resize(int w, int h) {
    proj = glm::perspective(glm::radians(V_FOV), (float)w / (float)h, Z_NEAR, Z_FAR);
    glViewport(0, 0, w, h);
}

void Camera::toggleFlyMode() {
    flyMode = !flyMode;
    if (!flyMode) {
        pos.y = floorY;
    }
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(pos, pos + front, up);
}

void Camera::updateDir() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getProjMatrix() {
    return proj;
}