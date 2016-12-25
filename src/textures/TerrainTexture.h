/*
 * TerrainTexture.h
 *
 *  Created on: 03 apr 2016
 *      Author: lorenzo
 */

#ifndef TEXTURES_TERRAINTEXTURE_H_
#define TEXTURES_TERRAINTEXTURE_H_

class TerrainTexture {
public:
    TerrainTexture(int textureID);
    virtual ~TerrainTexture();

    int getTextureID() const {
        return textureID;
    }

private:
    int textureID;
};

#endif /* TEXTURES_TERRAINTEXTURE_H_ */
