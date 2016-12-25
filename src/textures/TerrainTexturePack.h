/*
 * TerrainTexturePack.h
 *
 *  Created on: 03 apr 2016
 *      Author: lorenzo
 */

#ifndef TEXTURES_TERRAINTEXTUREPACK_H_
#define TEXTURES_TERRAINTEXTUREPACK_H_

#include "TerrainTexture.h"

class TerrainTexturePack {
public:
    TerrainTexturePack(TerrainTexture * backgroundTexture,
                       TerrainTexture * rTexture,
                       TerrainTexture * gTexture,
                       TerrainTexture * bTexture);
    virtual ~TerrainTexturePack();

    TerrainTexture * getBackgroundTexture() {
        return backgroundTexture;
    }

    TerrainTexture * getbTexture() {
        return bTexture;
    }

    TerrainTexture * getgTexture() {
        return gTexture;
    }

    TerrainTexture * getrTexture() {
        return rTexture;
    }

private:
    TerrainTexture * backgroundTexture;
    TerrainTexture * rTexture;
    TerrainTexture * gTexture;
    TerrainTexture * bTexture;
};

#endif /* TEXTURES_TERRAINTEXTUREPACK_H_ */
