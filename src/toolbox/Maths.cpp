/*
 * Maths.cpp
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#include "Maths.h"

Maths::Maths() {
}

Maths::~Maths() {
}

glm::mat4 Maths::createTransformationMatrix(glm::vec2 translation, glm::vec2 scale) {
    glm::mat4 matrix;
    matrix = glm::translate(glm::mat4(1.f), glm::vec3(translation.x, translation.y, 0));
    matrix = glm::scale(matrix, glm::vec3(scale.x, scale.y, 1.0f));
    return matrix;
}

glm::mat4 Maths::createTransformationMatrix(glm::vec3 translation,
                                            float rx, float ry, float rz, float scale) {

    glm::mat4 matrix;
    matrix = glm::translate(glm::mat4(1.f), translation);

    matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));

    matrix = glm::scale(matrix, glm::vec3(scale));

    return matrix;
}

glm::mat4 Maths::createViewMatrix(Camera * camera) {
    glm::mat4 viewMatrix;

    viewMatrix = glm::rotate(viewMatrix, glm::radians(camera->getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(camera->getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 cameraPos = camera->getPosition();
    glm::vec3 negativeCameraPos(-cameraPos.x, -cameraPos.y, -cameraPos.z);
    viewMatrix = glm::translate(viewMatrix, negativeCameraPos);

    return viewMatrix;
}
