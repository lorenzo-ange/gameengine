/*
 * SkyboxRenderer.cpp
 *
 *  Created on: 10 apr 2016
 *      Author: lorenzo
 */

#include "SkyboxRenderer.h"

const char * SkyboxRenderer::TEXTURE_FILES[6] = {
    "res/skybox/right.png",
    "res/skybox/left.png",
    "res/skybox/top.png",
    "res/skybox/bottom.png",
    "res/skybox/back.png",
    "res/skybox/front.png"
};
const char * SkyboxRenderer::NIGHT_TEXTURE_FILES[6] = {
    "res/skybox/nightRight.png",
    "res/skybox/nightLeft.png",
    "res/skybox/nightTop.png",
    "res/skybox/nightBottom.png",
    "res/skybox/nightBack.png",
    "res/skybox/nightFront.png"
};

const float SkyboxRenderer::SIZE = 500.0f;
// A simple cube
const float SkyboxRenderer::VERTICES[108] = {
    -SIZE,  SIZE, -SIZE,
    -SIZE, -SIZE, -SIZE,
     SIZE, -SIZE, -SIZE,
     SIZE, -SIZE, -SIZE,
     SIZE,  SIZE, -SIZE,
    -SIZE,  SIZE, -SIZE,

    -SIZE, -SIZE,  SIZE,
    -SIZE, -SIZE, -SIZE,
    -SIZE,  SIZE, -SIZE,
    -SIZE,  SIZE, -SIZE,
    -SIZE,  SIZE,  SIZE,
    -SIZE, -SIZE,  SIZE,

     SIZE, -SIZE, -SIZE,
     SIZE, -SIZE,  SIZE,
     SIZE,  SIZE,  SIZE,
     SIZE,  SIZE,  SIZE,
     SIZE,  SIZE, -SIZE,
     SIZE, -SIZE, -SIZE,

    -SIZE, -SIZE,  SIZE,
    -SIZE,  SIZE,  SIZE,
     SIZE,  SIZE,  SIZE,
     SIZE,  SIZE,  SIZE,
     SIZE, -SIZE,  SIZE,
    -SIZE, -SIZE,  SIZE,

    -SIZE,  SIZE, -SIZE,
     SIZE,  SIZE, -SIZE,
     SIZE,  SIZE,  SIZE,
     SIZE,  SIZE,  SIZE,
    -SIZE,  SIZE,  SIZE,
    -SIZE,  SIZE, -SIZE,

    -SIZE, -SIZE, -SIZE,
    -SIZE, -SIZE,  SIZE,
     SIZE, -SIZE, -SIZE,
     SIZE, -SIZE, -SIZE,
    -SIZE, -SIZE,  SIZE,
     SIZE, -SIZE,  SIZE
};

SkyboxRenderer::SkyboxRenderer(Loader* loader, glm::mat4 projectionMatrix) {
    time = 0;

    cube = new RawModel(loader->loadToVAO((float *)VERTICES, sizeof(VERTICES)/sizeof(float), 3));
    texture = loader->loadCubeMap(TEXTURE_FILES);
    nightTexture = loader->loadCubeMap(NIGHT_TEXTURE_FILES);
    shader = new SkyboxShader();
    shader->start();
    shader->connectTextureUnits();
    shader->loadProjectionMatrix(projectionMatrix);
    shader->stop();
}

SkyboxRenderer::~SkyboxRenderer() {
    delete cube;
    delete shader;
}

void SkyboxRenderer::render(Camera* camera, float r, float g, float b) {
    shader->start();
    shader->loadViewMatrix(camera);
    shader->loadFogColour(r, g, b);
    glBindVertexArray(cube->getVaoID());
    glEnableVertexAttribArray(0);
    bindTextures();
    glDrawArrays(GL_TRIANGLES, 0, cube->getVertexCount());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader->stop();
}

void SkyboxRenderer::cleanUp() {
    shader->cleanUp();
}

void SkyboxRenderer::bindTextures() {
    time += DisplayManager::getFrameTimeSeconds() * 100;
    time = fmod(time, 24000);
    int texture1;
    int texture2;
    float blendFactor;
    if(time >= 0 && time < 5000){
        texture1 = nightTexture;
        texture2 = nightTexture;
        blendFactor = (time - 0)/(5000 - 0);
    }else if(time >= 5000 && time < 8000){
        texture1 = nightTexture;
        texture2 = texture;
        blendFactor = (time - 5000)/(8000 - 5000);
    }else if(time >= 8000 && time < 21000){
        texture1 = texture;
        texture2 = texture;
        blendFactor = (time - 8000)/(21000 - 8000);
    }else{
        texture1 = texture;
        texture2 = nightTexture;
        blendFactor = (time - 21000)/(24000 - 21000);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture2);
    shader->loadBlendFactor(blendFactor);
}
