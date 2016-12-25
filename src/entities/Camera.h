/*
 * Camera.h
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#ifndef ENTITIES_CAMERA_H_
#define ENTITIES_CAMERA_H_

#include <glm/glm.hpp>
#include "../toolbox/Keyboard.h"
#include "Player.h"

class Camera {
public:
    Camera(Player * player);
    virtual ~Camera();

    float getPitch() const {
        return pitch;
    }

    void setPitch(float pitch) {
        this->pitch = pitch;
    }

    glm::vec3 getPosition() {
        return position;
    }

    float getYaw() const {
        return yaw;
    }

    void setYaw(float yaw) {
        this->yaw = yaw;
    }

    void move();

private:
    glm::vec3 position;
    float pitch;
    float yaw;

    Player * player;
    static const float DISTANCE_FROM_PLAYER;
    static const float ANGLE_AROUND_PLAYER;

    float calculateHorizontalDistance();
    float calculateVerticalDistance();
    void calculateCameraPosition(float horizDistance, float verticDistance);
};

#endif /* ENTITIES_CAMERA_H_ */
