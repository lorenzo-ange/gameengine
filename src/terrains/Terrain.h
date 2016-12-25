/*
 * Terrain.h
 *
 *  Created on: 02 apr 2016
 *      Author: lorenzo
 */

#ifndef TERRAINS_TERRAIN_H_
#define TERRAINS_TERRAIN_H_

#include <glm/glm.hpp>

#include "../models/RawModel.h"
#include "../textures/TerrainTexture.h"
#include "../textures/TerrainTexturePack.h"
#include "../renderEngine/Loader.h"

class Terrain {
public:
    Terrain(int gridX, int gridZ,
            Loader * loader,
            TerrainTexturePack * texturePack,
            TerrainTexture * blendMap,
            const char * heightMap);
    virtual ~Terrain();

    RawModel * getModel() {
        return model;
    }

    float getX() const {
        return x;
    }

    float getZ() const {
        return z;
    }

    TerrainTexture * getBlendMap() {
        return blendMap;
    }

    TerrainTexturePack * getTexturePack() {
        return texturePack;
    }

    float getHeightOfTerrain(float worldX, float worldZ);
private:
    static const float SIZE;
    static const float MAX_HEIGHT;
    static const float MAX_PIXEL_COLOUR;

    static float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);

    int vertexCount;
    float * heights = NULL;
    float x;
    float z;
    RawModel * model;
    TerrainTexturePack * texturePack;
    TerrainTexture * blendMap;

    RawModel generateTerrain(Loader * loader, const char * heightMap);
    float getHeight(int x, int z, std::vector<unsigned char> * image, int imageWidth, int imageHeight);
    glm::vec3 calculateNormal(int x, int z, std::vector<unsigned char> * image, int imageWidth, int imageHeight);

};

#endif /* TERRAINS_TERRAIN_H_ */
