/*
 * ModelTexture.cpp
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#include "ModelTexture.h"

ModelTexture::ModelTexture(int id) {
    textureID = id;
    shineDamper = 1;
    reflectivity = 0;

    hasTransparency = false;
    useFakeLighting = false;
    numberOfRows = 1;
}

ModelTexture::~ModelTexture() {
}

