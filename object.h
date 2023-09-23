//
// Created by bmneu on 9/22/2023.
//

#ifndef CUBELANDS_OBJECT_H
#define CUBELANDS_OBJECT_H

#include <memory>
#include "texture.h"

class Object {
public:
    Object(const std::shared_ptr<Texture>& texture, float width);
    void draw();
private:
    float width;
    float height;
    const std::shared_ptr<Texture>& texture;
};


#endif //CUBELANDS_OBJECT_H
