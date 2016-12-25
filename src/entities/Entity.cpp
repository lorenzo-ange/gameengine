/*
 * Entity.cpp
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#include "Entity.h"

Entity::Entity(TexturedModel * model,
               glm::vec3 position,
               float rotX, float rotY, float rotZ,
               float scale) {
    this->model = model;
    this->position = position;
    this->rotX = rotX;
    this->rotY = rotY;
    this->rotZ = rotZ;
    this->scale = scale;
    textureIndex = 0;
}

Entity::Entity(TexturedModel * model,
               int index,
               glm::vec3 position,
               float rotX, float rotY, float rotZ,
               float scale) {
    this->model = model;
    this->position = position;
    this->rotX = rotX;
    this->rotY = rotY;
    this->rotZ = rotZ;
    this->scale = scale;
    textureIndex = index;
}

Entity::~Entity() {
}

void Entity::increasePosition(float dx, float dy, float dz) {
    this->position.x += dx;
    this->position.y += dy;
    this->position.z += dz;
}

void Entity::increaseRotation(float dx, float dy, float dz) {
    this->rotX += dx;
    this->rotY += dy;
    this->rotZ += dz;
}

float Entity::getTextureXOffset() {
    int column = textureIndex % model->getTexture()->getNumberOfRows();
    return (float) column / (float) model->getTexture()->getNumberOfRows();
}

float Entity::getTextureYOffset() {
    int row = textureIndex / model->getTexture()->getNumberOfRows();
    return (float) row / (float) model->getTexture()->getNumberOfRows();
}
