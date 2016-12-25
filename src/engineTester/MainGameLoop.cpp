#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../models/RawModel.h"
#include "../models/TexturedModel.h"
#include "../textures/ModelTexture.h"
#include "../guis/GuiTexture.h"
#include "../guis/GuiRenderer.h"
#include "../shaders/StaticShader.h"
#include "../renderEngine/OBJLoader.h"
#include "../terrains/Terrain.h"
#include "../entities/Player.h"
#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>
#include "../renderEngine/EntityRenderer.h"
#include "../renderEngine/MasterRenderer.h"

int main(void) {
    DisplayManager::createDisplay();
    Loader loader;

    TerrainTexture backgroundTexture(loader.loadTexture("res/textures/grass.png"));
    TerrainTexture rTexture(loader.loadTexture("res/textures/mud.png"));
    TerrainTexture gTexture(loader.loadTexture("res/textures/grassFlowers.png"));
    TerrainTexture bTexture(loader.loadTexture("res/textures/path.png"));

    TerrainTexturePack texturePack(&backgroundTexture, &rTexture, &gTexture, &bTexture);
    TerrainTexture blendMap(loader.loadTexture("res/textures/blendMap.png"));

    Terrain terrain(0, -1, &loader, &texturePack, &blendMap, "res/textures/heightMap.png");

    RawModel lpTreeModel = OBJLoader::loadObjModel("res/models/lowPolyTree.obj", &loader);
    ModelTexture lpTreeModelTexture(loader.loadTexture("res/textures/lowPolyTreeAtlas.png"));
    lpTreeModelTexture.setNumberOfRows(2);
    TexturedModel lpTreeStaticModel(&lpTreeModel, &lpTreeModelTexture);

    RawModel grassModel = OBJLoader::loadObjModel("res/models/grassModel.obj", &loader);
    ModelTexture grassModelTexture(loader.loadTexture("res/textures/grassTexture.png"));
    grassModelTexture.setHasTransparency(true);
    grassModelTexture.setUseFakeLighting(true);
    TexturedModel grassStaticModel(&grassModel, &grassModelTexture);

    RawModel flowerModel = OBJLoader::loadObjModel("res/models/grassModel.obj", &loader);
    ModelTexture flowerModelTexture(loader.loadTexture("res/textures/flower.png"));
    flowerModelTexture.setHasTransparency(true);
    flowerModelTexture.setUseFakeLighting(true);
    TexturedModel flowerStaticModel(&flowerModel, &flowerModelTexture);

    RawModel fernModel = OBJLoader::loadObjModel("res/models/fern.obj", &loader);
    ModelTexture fernTextureAtlas(loader.loadTexture("res/textures/fern.png"));
    fernTextureAtlas.setHasTransparency(true);
    fernTextureAtlas.setNumberOfRows(2);
    TexturedModel fernStaticModel(&fernModel, &fernTextureAtlas);

    std::vector<Entity *> entities;
    for(int i=0;i<500;i++){
        float rand1 = (float) (rand() % 1000) / 1000;
        float rand2 = (float) (rand() % 1000) / 1000;
        float rand3 = (float) ((rand() % 500) + 400) / 1000;
        float rand4 = (float) (rand() % 4);

        float x = rand1*800;
        float z = rand2 * -800;
        float y = terrain.getHeightOfTerrain(x, z);

        float type = rand() % 100;
        if(type <= 30) {
            entities.push_back(new Entity(&lpTreeStaticModel, rand4, glm::vec3(x, y, z), 0, type*10, 0, rand3));
        }
        else if(type <= 40) {
            entities.push_back(new Entity(&flowerStaticModel, glm::vec3(x, y, z), 0, 0, 0, 1));
        }
        else if(type <= 75) {
            entities.push_back(new Entity(&grassStaticModel, glm::vec3(x, y, z), 0, 0, 0, 1));
        }
        else {
            entities.push_back(new Entity(&fernStaticModel, rand4, glm::vec3(x, y, z), 0, type*10, 0, 0.5));
        }
    }

    RawModel lampModel = OBJLoader::loadObjModel("res/models/lamp.obj", &loader);
    ModelTexture lampModelTexture(loader.loadTexture("res/textures/lamp.png"));
    lampModelTexture.setUseFakeLighting(true);
    TexturedModel lampStaticModel(&lampModel, &lampModelTexture);
    entities.push_back(new Entity(&lampStaticModel, glm::vec3(185, terrain.getHeightOfTerrain(185, -293), -293), 0, 0, 0, 1));
    entities.push_back(new Entity(&lampStaticModel, glm::vec3(370, terrain.getHeightOfTerrain(370, -300), -300), 0, 0, 0, 1));
    entities.push_back(new Entity(&lampStaticModel, glm::vec3(293, terrain.getHeightOfTerrain(293, -305), -305), 0, 0, 0, 1));


    std::vector<Light *> lights;
    lights.push_back(new Light(glm::vec3(0, 10000, -7000), glm::vec3(0.4, 0.4, 0.4)));
    lights.push_back(new Light(glm::vec3(185, terrain.getHeightOfTerrain(185, -293) + 14, -293), glm::vec3(3, 0, 0), glm::vec3(1, 0.01, 0.002)));
    lights.push_back(new Light(glm::vec3(370, terrain.getHeightOfTerrain(370, -300) + 14, -300), glm::vec3(0, 3, 3), glm::vec3(1, 0.01, 0.002)));
    lights.push_back(new Light(glm::vec3(293, terrain.getHeightOfTerrain(293, -305) + 14, -305), glm::vec3(3, 3, 0), glm::vec3(1, 0.01, 0.002)));

    RawModel playerModel = OBJLoader::loadObjModel("res/models/falcon.obj", &loader);
    ModelTexture playerModelTexture(loader.loadTexture("res/textures/falcon.png"));
    playerModelTexture.setShineDamper(10.0f);
    playerModelTexture.setReflectivity(1.0f);
    TexturedModel playerStaticModel(&playerModel, &playerModelTexture);
    Player player(&playerStaticModel, glm::vec3(400.0f, 0.0f, -400.0f), 0.0f, 0.0f, 0.0f, 0.5f);

    Camera camera(&player);

    MasterRenderer renderer(&loader);

    std::vector<GuiTexture *> guis;
    GuiTexture gui(loader.loadTexture("res/guis/health.png"), glm::vec2(-0.7f, -0.9f), glm::vec2(0.25f, 0.25f));
    guis.push_back(&gui);

    GuiTexture quit(loader.loadTexture("res/guis/exit.png"), glm::vec2(0.0f, 0.3f), glm::vec2(0.8f, 0.8f));
    bool isQuitMenuOpen = false;

    GuiTexture smoke(loader.loadTexture("res/guis/smoke.png"), glm::vec2(0.0f, -0.5f), glm::vec2(0.2f, 0.2f));
    int smokeCount = 0;

    GuiRenderer guiRenderer(&loader);

    Keyboard keyboard;
    bool isCloseRequested = false;
    SDL_Event event;

    while (!isCloseRequested){
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_CLOSE) {
                isCloseRequested = true;
            }
            else if(event.type == SDL_KEYDOWN ||
                    event.type == SDL_KEYUP) {
                keyboard.handleSDLEvent(&event);
            }
        }

        if(isQuitMenuOpen) {
            if(keyboard.isKeyDown(Keyboard::GameKey::GK_Y)){
                isCloseRequested = true;
            }
            else if(keyboard.isKeyDown(Keyboard::GameKey::GK_N)){
                isQuitMenuOpen = false;
                guis.pop_back();
            }
            continue;
        }

        renderer.processTerrain(&terrain);

        for(unsigned int i = 0; i < entities.size(); i++){
            renderer.processEntity(entities[i]);
        }

        player.move(&keyboard, &terrain);
        camera.move();

        renderer.processEntity(&player);

        renderer.render(&lights, &camera);

        // Smoke effect
        if(keyboard.isKeyDown(Keyboard::GameKey::GK_SPACE)) {
            if(smokeCount < 10) {
                smokeCount++;
                guis.push_back(&smoke);
            }
            else {
                smokeCount -= 9;
                for(int i = 0; i<9; i++) {
                    guis.pop_back();
                }
            }
        }
        else {
            while(smokeCount > 0) {
                smokeCount--;
                guis.pop_back();
            }
        }

        if(keyboard.isKeyDown(Keyboard::GameKey::GK_Q)) {
            isQuitMenuOpen = true;
            guis.push_back(&quit);
        }

        guiRenderer.render(&guis);
        DisplayManager::updateDisplay();
    }

    for(unsigned int i = 0; i < entities.size(); i++){
        delete entities[i];
    }
    for(unsigned int i = 0; i < lights.size(); i++){
        delete lights[i];
    }

    guiRenderer.cleanUp();
    renderer.cleanUp();
    loader.cleanUp();
    DisplayManager::closeDisplay();
    return EXIT_SUCCESS;
}
