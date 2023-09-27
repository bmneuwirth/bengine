//
// Created by bmneu on 9/22/2023.
//

#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include <iostream>
#include <GL/glew.h>

Texture::Texture(const char *filePath) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int nrChannels;
    unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    if (data)
    {
        // TODO: Support png and other formats (right now only png)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "Texture creation error: " << err << std::endl;
    }
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, texture);
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}
