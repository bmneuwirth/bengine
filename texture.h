//
// Created by bmneu on 9/22/2023.
//

#ifndef CUBELANDS_TEXTURE_H
#define CUBELANDS_TEXTURE_H

class Texture {
public:
    explicit Texture(const char* filePath);
    void bind() const;

    int getWidth();
    int getHeight();

private:
    unsigned int texture;
    int width;
    int height;
};


#endif //CUBELANDS_TEXTURE_H
