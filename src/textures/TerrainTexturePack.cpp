/*
 * TerrainTexturePack.cpp
 *
 *  Created on: 03 apr 2016
 *      Author: lorenzo
 */

#include "TerrainTexturePack.h"

TerrainTexturePack::TerrainTexturePack(TerrainTexture * backgroundTexture,
                                       TerrainTexture * rTexture,
                                       TerrainTexture * gTexture,
                                       TerrainTexture * bTexture) {

    this->backgroundTexture = backgroundTexture;
    this->rTexture = rTexture;
    this->bTexture = bTexture;
    this->gTexture = gTexture;
}

TerrainTexturePack::~TerrainTexturePack() {
}

