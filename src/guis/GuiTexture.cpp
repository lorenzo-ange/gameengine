/*
 * GuiTexture.cpp
 *
 *  Created on: 06 apr 2016
 *      Author: lorenzo
 */

#include "GuiTexture.h"

GuiTexture::GuiTexture(int texture, glm::vec2 position, glm::vec2 scale) {
    this->texture = texture;
    this->position = position;
    this->scale = scale;
}

GuiTexture::~GuiTexture() {
}

