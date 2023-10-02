//
// Created by bmneu on 9/22/2023.
//

#ifndef CUBELANDS_OBJECT_H
#define CUBELANDS_OBJECT_H

#include <memory>
#include <glm/glm.hpp>
#include "texture.h"

/**
 * A class that represents a rectangular prism in the world.
 * Objects have textures and can be rendered to the screen.
 */
class Object {
public:
    /**
     * Creates a cube object with a given position, rotation, and scale
     * @param texture the texture for the cube object
     * @param pos the position in world space of the cube
     * @param rot the rotation matrix of the cube
     * @param scale the scale factors of the cube
     */
    explicit Object(std::shared_ptr<Texture> texture, glm::vec3 pos = glm::vec3(0, 0, 0), glm::mat4 rot = glm::mat4(1.0f), glm::vec3 scale = glm::vec3(1.0f));

    /**
     * Returns the model matrix corresponding to the object
     * @return the model matrix corresponding to the object
     */
    glm::mat4 getModel();

    /**
     * Returns the texture corresponding to the object
     * @return the texture corresponding to the object
     */
    std::shared_ptr<Texture> getTexture();

    /**
     * Sets the position of the object in world space
     * @param pos the position to set to
     */
    void setPos(glm::vec3 pos);

    /**
     * Sets the x value of the object in world space
     * @param x the x position to set to
     */
    void setX(float x);

    /**
     * Sets the y value of the object in world space
     * @param y the y position to set to
     */
    void setY(float y);

    /**
     * Sets the z value of the object in world space
     * @param z the z position to set to
     */
    void setZ(float z);

    /**
     * Sets the rotation matrix of the object in world space
     * @param rot the rotation matrix to set to
     */
    void setRot(glm::mat4 rot);

    /**
     * Sets the scale of the object
     * @param scale the scale to set to (applied to all axes)
     */
    void setScale(float scale);

    /**
     * Returns the number of vertices associated with the object
     * @return the number of vertices associated with the object
     */
    int getVertCount();

private:
    /**
     * Updates the model matrix based on the position, rotation, and scale of the object
     */
    void updateModel();

    std::shared_ptr<Texture> texture;
    glm::mat4 model;
    glm::vec3 pos;
    glm::mat4 rot;
    glm::vec3 scale;

    int vertCount;
    // Whether the model matrix needs to be updated next time it is retrieved
    bool shouldUpdate;
};


#endif //CUBELANDS_OBJECT_H
