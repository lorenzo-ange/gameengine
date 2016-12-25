/*
 * Entity.h
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#ifndef ENTITIES_ENTITY_H_
#define ENTITIES_ENTITY_H_

#include "../models/TexturedModel.h"
#include <glm/glm.hpp>

class Entity {
public:
    Entity(TexturedModel * model,
           glm::vec3 position,
           float rotX, float rotY, float rotZ,
           float scale);
    Entity(TexturedModel * model,
           int index,
           glm::vec3 position,
           float rotX, float rotY, float rotZ,
           float scale);
    virtual ~Entity();

    void increasePosition(float dx, float dy, float dz);
    void increaseRotation(float dx, float dy, float dz);

    float getTextureXOffset();
    float getTextureYOffset();

    glm::vec3 getPosition() {
        return position;
    }

    void setPosition(glm::vec3 position) {
        this->position = position;
    }

    float getRotX() const {
        return rotX;
    }

    void setRotX(float rotX) {
        this->rotX = rotX;
    }

    float getRotY() const {
        return rotY;
    }

    void setRotY(float rotY) {
        this->rotY = rotY;
    }

    float getRotZ() const {
        return rotZ;
    }

    void setRotZ(float rotZ) {
        this->rotZ = rotZ;
    }

    float getScale() const {
        return scale;
    }

    void setScale(float scale) {
        this->scale = scale;
    }

    TexturedModel * getModel() {
        return model;
    }

    void setModel(TexturedModel * model) {
        this->model = model;
    }

protected:
    TexturedModel * model;
    glm::vec3 position;
    float rotX, rotY, rotZ;
    float scale;
    int textureIndex;
};

#endif /* ENTITIES_ENTITY_H_ */
