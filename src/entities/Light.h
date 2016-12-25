/*
 * Light.h
 *
 *  Created on: 31 mar 2016
 *      Author: lorenzo
 */

#ifndef ENTITIES_LIGHT_H_
#define ENTITIES_LIGHT_H_

#include <glm/glm.hpp>

class Light {
public:
    Light(glm::vec3 position, glm::vec3 colour);
    Light(glm::vec3 position, glm::vec3 colour, glm::vec3 attenuation);
    virtual ~Light();

    glm::vec3 getColour() const {
        return colour;
    }

    void setColour(glm::vec3 colour) {
        this->colour = colour;
    }

    glm::vec3 getPosition() const {
        return position;
    }

    void setPosition(glm::vec3 position) {
        this->position = position;
    }

    const glm::vec3 getAttenuation() const {
        return attenuation;
    }

private:
    glm::vec3 position;
    glm::vec3 colour;
    glm::vec3 attenuation;
};

#endif /* ENTITIES_LIGHT_H_ */
