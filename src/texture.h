//
// Created by bmneu on 9/22/2023.
//

#ifndef CUBELANDS_TEXTURE_H
#define CUBELANDS_TEXTURE_H

/**
 * A class representing an OpenGL texture that can be applied to an object.
 *
 * Textures are loaded from an image and can be bound to be used when rendering.
 */
class Texture {
public:
    /**
     * Creates a texture
     * @param filePath the location of the image for the texture
     */
    explicit Texture(const char* filePath);

    /**
     * Bind the current texture
     */
    void bind() const;

    /**
     * Gets the width of the texture
     * @return the width of the texture
     */
    int getWidth() const;

    /**
     * Gets the height of the texture
     * @return the height of the texture
     */
    int getHeight() const;

private:
    unsigned int texture;
    int width;
    int height;
};


#endif //CUBELANDS_TEXTURE_H
