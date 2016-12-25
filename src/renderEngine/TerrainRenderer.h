/*
 * TerrainRenderer.h
 *
 *  Created on: 02 apr 2016
 *      Author: lorenzo
 */

#ifndef RENDERENGINE_TERRAINRENDERER_H_
#define RENDERENGINE_TERRAINRENDERER_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "../models/RawModel.h"
#include "../shaders/TerrainShader.h"
#include "../toolbox/Maths.h"
#include "../terrains/Terrain.h"

class TerrainRenderer {
public:
    TerrainRenderer(TerrainShader * shader, glm::mat4 projectionMatrix);
    virtual ~TerrainRenderer();

    void render(std::vector<Terrain *> * terrains);

private:
    TerrainShader * shader;

    void bindTextures(Terrain * terrain);
    void prepareTerrain(Terrain * terrain);
    void unbindTexturedModel();
    void loadModelMatrix(Terrain * terrain);
};

#endif /* RENDERENGINE_TERRAINRENDERER_H_ */
