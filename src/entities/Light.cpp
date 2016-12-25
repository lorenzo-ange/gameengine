/*
 * Light.cpp
 *
 *  Created on: 31 mar 2016
 *      Author: lorenzo
 */

#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 colour) {
    this->position = position;
    this->colour = colour;
    this->attenuation = glm::vec3(1, 0, 0);
}

Light::~Light() {
}

Light::Light(glm::vec3 position, glm::vec3 colour, glm::vec3 attenuation) {
    this->position = position;
    this->colour = colour;
    this->attenuation = attenuation;
}
