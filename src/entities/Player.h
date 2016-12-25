/*
 * Player.h
 *
 *  Created on: 03 apr 2016
 *      Author: lorenzo
 */

#ifndef ENTITIES_PLAYER_H_
#define ENTITIES_PLAYER_H_

#include <glm/glm.hpp>

#include "../renderEngine/DisplayManager.h"
#include "../toolbox/Keyboard.h"
#include "../terrains/Terrain.h"
#include "Entity.h"

class Player: public Entity {
public:
    Player(TexturedModel * model,
           glm::vec3 position,
           float rotX, float rotY, float rotZ,
           float scale);
    virtual ~Player();

    void move(Keyboard * keyboard, Terrain * terrain);

private:
    static const float RUN_SPEED;
    static const float TURN_SPEED;
    static const float WINGS_INCLINATION_SPEED;
    static const float WINGS_INCLINATION_LIMIT;

    float currentSpeed;
    float currentTurnSpeed;
    float currentWingsInclinationSpeed;

    void checkInputs(Keyboard * keyboard);
};

#endif /* ENTITIES_PLAYER_H_ */
