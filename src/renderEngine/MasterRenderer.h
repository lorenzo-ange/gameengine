/*
 * MasterRenderer.h
 *
 *  Created on: 01 apr 2016
 *      Author: lorenzo
 */

#ifndef RENDERENGINE_MASTERRENDERER_H_
#define RENDERENGINE_MASTERRENDERER_H_

#include "../skybox/SkyboxRenderer.h"
#include "Loader.h"
#include "../shaders/StaticShader.h"
#include "../shaders/TerrainShader.h"
#include "../terrains/Terrain.h"
#include <vector>
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "DisplayManager.h"

class MasterRenderer {
public:
    MasterRenderer(Loader * loader);
    virtual ~MasterRenderer();

    void processEntity(Entity * entity);
    void processTerrain(Terrain * terrain);
    void render(std::vector<Light *> * lights, Camera * camera);
    void cleanUp();

    static void enableCulling();
    static void disableCulling();
private:
    static const float FOV;
    static const float NEAR_PLANE;
    static const float FAR_PLANE;

    static const float SKY_R;
    static const float SKY_G;
    static const float SKY_B;

    glm::mat4 projectionMatrix;

    StaticShader * shader;
    EntityRenderer * renderer;
    std::vector<TModelEntities> entities;

    TerrainRenderer * terrainRenderer;
    TerrainShader * terrainShader;
    std::vector<Terrain *> terrains;

    SkyboxRenderer * skyboxRenderer;

    void prepare();
    void createProjectionMatrix();
};

#endif /* RENDERENGINE_MASTERRENDERER_H_ */
