/*
 * MasterRenderer.cpp
 *
 *  Created on: 01 apr 2016
 *      Author: lorenzo
 */

#include "MasterRenderer.h"

const float MasterRenderer::FOV = 70;
const float MasterRenderer::NEAR_PLANE = 0.1f;
const float MasterRenderer::FAR_PLANE = 1000;

const float MasterRenderer::SKY_R = 0.5444f;
const float MasterRenderer::SKY_G = 0.62f;
const float MasterRenderer::SKY_B = 0.69f;

MasterRenderer::MasterRenderer(Loader * loader) {
    shader = new StaticShader();
    terrainShader = new TerrainShader();

    enableCulling();
    createProjectionMatrix();
    renderer = new EntityRenderer(shader, projectionMatrix);
    terrainRenderer = new TerrainRenderer(terrainShader, projectionMatrix);
    skyboxRenderer = new SkyboxRenderer(loader, projectionMatrix);
}

MasterRenderer::~MasterRenderer() {
    delete shader;
    delete renderer;

    delete terrainShader;
    delete terrainRenderer;
    delete skyboxRenderer;
}

void MasterRenderer::render(std::vector<Light *> * lights, Camera* camera) {
    prepare();
    shader->start();
    shader->loadSkyColour(SKY_R, SKY_G, SKY_B);
    shader->loadLights(lights);
    shader->loadViewMatrix(camera);
    renderer->render(&entities);
    shader->stop();

    terrainShader->start();
    terrainShader->loadSkyColour(SKY_R, SKY_G, SKY_B);
    terrainShader->loadLights(lights);
    terrainShader->loadViewMatrix(camera);
    terrainRenderer->render(&terrains);
    terrainShader->stop();

    skyboxRenderer->render(camera, SKY_R, SKY_G, SKY_B);

    terrains.clear();
    entities.clear();
}

void MasterRenderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(SKY_R, SKY_G, SKY_B, 1);
}

void MasterRenderer::processTerrain(Terrain* terrain) {
    terrains.push_back(terrain);
}

void MasterRenderer::createProjectionMatrix() {
    float aspectRatio = (float) DisplayManager::getWidth() / (float) DisplayManager::getHeight();
    float y_scale = (float) ((1.0f / glm::tan(glm::radians(FOV / 2.0f))) * aspectRatio);
    float x_scale = y_scale / aspectRatio;
    float frustum_length = FAR_PLANE - NEAR_PLANE;

    float tmp[16] = { x_scale, 0, 0, 0,
                      0, y_scale, 0, 0,
                      0, 0, -((FAR_PLANE + NEAR_PLANE) / frustum_length), -1,
                      0, 0, -((2 * NEAR_PLANE * FAR_PLANE) / frustum_length), 0
                    };
    memcpy(glm::value_ptr(projectionMatrix), tmp, sizeof(tmp));
}

void MasterRenderer::processEntity(Entity* entity) {
    TexturedModel * entityModel = entity->getModel();
    bool processed = false;

    for(unsigned int i = 0; i < entities.size(); i++) {
        if(entityModel == entities[i].texturedModel) {
            // An entity with same 3d model already in our 3d scene, add to its list
            entities[i].entities.push_back(entity);
            processed = true;
            break;
        }
    }
    if(processed) {
        return;
    }

    // New 3d model, not already in our 3d scene
    std::vector<Entity *> entitiesList;
    entitiesList.push_back(entity);
    TModelEntities tme = {entityModel, entitiesList};
    entities.push_back(tme);
}

void MasterRenderer::cleanUp() {
    shader->cleanUp();
    terrainShader->cleanUp();
    skyboxRenderer->cleanUp();
}

void MasterRenderer::enableCulling() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void MasterRenderer::disableCulling() {
    glDisable(GL_CULL_FACE);
}
