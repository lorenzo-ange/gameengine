/*
 * Camera.cpp
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#include "Camera.h"

const float Camera::DISTANCE_FROM_PLAYER = 8;
const float Camera::ANGLE_AROUND_PLAYER = 0;

Camera::Camera(Player* player) {
    this->player = player;
    this->position = glm::vec3(0, 0, 0);
    this->pitch = 0;
    this->yaw = 0;
}

Camera::~Camera() {
}

void Camera::move() {
    float horizontalDistance = 8;//calculateHorizontalDistance();
    float verticalDistance = 2;//calculateVerticalDistance();
    calculateCameraPosition(horizontalDistance, verticalDistance);
    yaw = 180 - (player->getRotY() + ANGLE_AROUND_PLAYER);
}

float Camera::calculateHorizontalDistance() {
    return (float) (DISTANCE_FROM_PLAYER * cos(glm::radians(pitch)));
}

float Camera::calculateVerticalDistance() {
    return (float) (DISTANCE_FROM_PLAYER * sin(glm::radians(pitch)));
}

void Camera::calculateCameraPosition(float horizDistance, float verticDistance) {
    float theta = player->getRotY() + ANGLE_AROUND_PLAYER;
    float offsetX = horizDistance * (float) sin(glm::radians(theta));
    float offsetZ = horizDistance * (float) cos(glm::radians(theta));
    position.x = player->getPosition().x - offsetX;
    position.z = player->getPosition().z - offsetZ;
    position.y = player->getPosition().y + verticDistance;
}
