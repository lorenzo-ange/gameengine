/*
 * Player.cpp
 *
 *  Created on: 03 apr 2016
 *      Author: lorenzo
 */

#include "Player.h"

const float Player::RUN_SPEED = 40;
const float Player::TURN_SPEED = 140;
const float Player::WINGS_INCLINATION_SPEED = 100;
const float Player::WINGS_INCLINATION_LIMIT = 40;

Player::Player(TexturedModel* model,
               glm::vec3 position,
               float rotX, float rotY, float rotZ,
               float scale) : Entity(model, position, rotX, rotY, rotZ, scale) {

    currentSpeed = 0;
    currentTurnSpeed = 0;
    currentWingsInclinationSpeed = 0;
}

Player::~Player() {
}

void Player::move(Keyboard * keyboard, Terrain * terrain) {
    checkInputs(keyboard);
    increaseRotation(0, currentTurnSpeed * DisplayManager::getFrameTimeSeconds(),
                     currentWingsInclinationSpeed * DisplayManager::getFrameTimeSeconds());
    float distance = currentSpeed * DisplayManager::getFrameTimeSeconds();
    float dx = distance * (float) sin(glm::radians(getRotY()));
    float dz = distance * (float) cos(glm::radians(getRotY()));
    increasePosition(dx, 0, dz);

    float terrainHeight = terrain->getHeightOfTerrain(getPosition().x, getPosition().z);
    position.y = terrainHeight + 5.0f;
}

void Player::checkInputs(Keyboard* keyboard) {

    if(keyboard->isKeyDown(Keyboard::GK_UP)) {
        currentSpeed = RUN_SPEED;
    }
    else if(keyboard->isKeyDown(Keyboard::GK_DOWN)) {
        currentSpeed = -RUN_SPEED;
    }
    else {
        currentSpeed = 0;
    }

    if(keyboard->isKeyDown(Keyboard::GK_SPACE)) {
        // Turbo speed
        currentSpeed = RUN_SPEED*5;
    }

    if(keyboard->isKeyDown(Keyboard::GK_RIGHT)) {
        currentTurnSpeed = -TURN_SPEED;
        currentWingsInclinationSpeed = rotZ < WINGS_INCLINATION_LIMIT ? WINGS_INCLINATION_SPEED : 0;
    }
    else if(keyboard->isKeyDown(Keyboard::GK_LEFT)) {
        currentTurnSpeed = TURN_SPEED;
        currentWingsInclinationSpeed = rotZ > -WINGS_INCLINATION_LIMIT ? -WINGS_INCLINATION_SPEED : 0;

    }
    else {
        // If arrow keys are not pressed, roll back the inclination of the wings
        currentTurnSpeed = 0;
        if(rotZ < 5 && rotZ > -5) {
            rotZ = 0;
            currentWingsInclinationSpeed = 0;
        }
        else {
            currentWingsInclinationSpeed = rotZ > 0 ? -WINGS_INCLINATION_SPEED : WINGS_INCLINATION_SPEED;
        }
    }
}
