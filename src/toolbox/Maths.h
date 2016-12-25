/*
 * Maths.h
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#ifndef TOOLBOX_MATHS_H_
#define TOOLBOX_MATHS_H_

#include "../entities/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Maths {
public:
    Maths();
    virtual ~Maths();

    static glm::mat4 createTransformationMatrix(glm::vec2 translation, glm::vec2 scale);
    static glm::mat4 createTransformationMatrix(glm::vec3 translation,
                                                float rx, float ry, float rz, float scale);
    static glm::mat4 createViewMatrix(Camera * camera);
};

#endif /* TOOLBOX_MATHS_H_ */
