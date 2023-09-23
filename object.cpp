//
// Created by bmneu on 9/22/2023.
//

#include "object.h"

Object::Object(const std::shared_ptr<Texture>& texture, float width) : texture(texture), width(width) {
    this->height = float(texture->getHeight()) * width / float(texture->getWidth());
}

void Object::draw() {

}
