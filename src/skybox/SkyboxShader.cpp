/*
 * SkyboxShader.cpp
 *
 *  Created on: 10 apr 2016
 *      Author: lorenzo
 */

#include "SkyboxShader.h"

const float SkyboxShader::ROTATION_SPEED = 0.3f;
const char * SkyboxShader::VERTEX_FILE = "src/skybox/skyboxVertexShader.txt";
const char * SkyboxShader::FRAGMENT_FILE = "src/skybox/skyboxFragmentShader.txt";

SkyboxShader::SkyboxShader() {
    init(VERTEX_FILE, FRAGMENT_FILE);

    rotation = 0.0f;
}

SkyboxShader::~SkyboxShader() {
}

void SkyboxShader::loadViewMatrix(Camera * camera) {
    glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
    // Don't trasate with the camera, only rotate with it
    viewMatrix[3] = glm::vec4(0, 0, 0, 1);
    // Skybox slow rotation
    rotation += ROTATION_SPEED * DisplayManager::getFrameTimeSeconds();
    viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    loadMatrix(location_viewMatrix, viewMatrix);
}

void SkyboxShader::loadProjectionMatrix(glm::mat4 projection) {
    loadMatrix(location_projectiontionMatrix, projection);
}

void SkyboxShader::loadFogColour(float r, float g, float b) {
    loadVector(location_fogColour, glm::vec3(r, g, b));
}

void SkyboxShader::loadBlendFactor(float blendFactor) {
    loadFloat(location_blendFactor, blendFactor);
}

void SkyboxShader::connectTextureUnits() {
    loadInt(location_cubeMap, 0);
    loadInt(location_cubeMap2, 1);
}

void SkyboxShader::getAllUniformLocations() {
    location_projectiontionMatrix = getUniformLocation("projectionMatrix");
    location_viewMatrix = getUniformLocation("viewMatrix");
    location_fogColour = getUniformLocation("fogColour");
    location_cubeMap = getUniformLocation("cubeMap");
    location_cubeMap2 = getUniformLocation("cubeMap2");
    location_blendFactor = getUniformLocation("blendFactor");
}

void SkyboxShader::bindAttributes() {
    bindAttribute(0, "position");
}
