//
// Created by Ben Neuwirth on 9/30/23.
//

#ifndef CUBELANDS_CAMERA_H
#define CUBELANDS_CAMERA_H

#include <glm/glm.hpp>

/**
 * A class representing the camera used when rendering in the scene.
 * The camera has a position and direction, as well as other properties such as FOV.
 */
class Camera {
public:
    /**
     * Creates a camera
     * @param screenWidth the width of the screen window
     * @param screenHeight the height of the screen window
     * @param pos the position of the camera in world coordinates to start
     * @param up the world up direction in world space
     * @param flyMode whether the camera should be able to fly around or be fixed to the ground
     */
    Camera(int screenWidth, int screenHeight, glm::vec3 pos, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), bool flyMode = false);

    /**
     * Updates the camera position based on movement
     * @param dt delta time
     * @param forwardAmt how much to move the camera forward / backward as proportion of speed
     * @param rightAmt how much to move the camera right / left as proportion of speed
     */
    void processMovement(float dt, float forwardAmt, float rightAmt);

    /**
     * Updates the camera direction based on mouse movement
     * @param xOffset the change in pixel coordinates in x of the mouse
     * @param yOffset the change in pixel coordinates in y of the mouse
     */
    void processMouse(float xOffset, float yOffset);

    /**
    * Resizes the camera viewport
    * @param w the new width in pixels
    * @param h the new height in pixels
    */
    void resize(int w, int h);

    /**
     * Returns the view matrix associated with the camera
     * @return the view matrix associated with the camera
     */
    glm::mat4 getViewMatrix();

    /**
     * Returns the projection matrix associated with the camera
     * @return the projection matrix associated with the camera
     */
    glm::mat4 getProjMatrix();

private:
    /**
     * Updates the front, right, and up vectors based on the euler angles
     */
    void updateDir();

    glm::mat4 proj;

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
