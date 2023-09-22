//
// Created by bmneu on 9/22/2023.
//

#ifndef CUBELANDS_TEXTURE_H
#define CUBELANDS_TEXTURE_H

class Texture {
public:
    explicit Texture(const char* filePath);
    void bind() const;
    unsigned int texture;
private:
};


#endif //CUBELANDS_TEXTURE_H
