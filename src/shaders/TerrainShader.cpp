/*
 * TerrainShader.cpp
 *
 *  Created on: 02 apr 2016
 *      Author: lorenzo
 */

#include "TerrainShader.h"

const unsigned int TerrainShader::MAX_LIGHTS = 4;
const char * TerrainShader::VERTEX_FILE = "src/shaders/terrainVertexShader.txt";
const char * TerrainShader::FRAGMENT_FILE = "src/shaders/terrainFragmentShader.txt";

TerrainShader::TerrainShader() {
    init(VERTEX_FILE, FRAGMENT_FILE);
}

TerrainShader::~TerrainShader() {
    delete[] location_lightColour;
    delete[] location_lightPosition;
    delete[] location_attenuation;
}

void TerrainShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
    bindAttribute(2, "normal");
}

void TerrainShader::loadTransformationMatrix(glm::mat4 matrix) {
    loadMatrix(location_transformationMatrix, matrix);
}

void TerrainShader::loadViewMatrix(Camera * camera) {
    glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
    loadMatrix(location_viewMatrix, viewMatrix);
}

void TerrainShader::loadProjectionMatrix(glm::mat4 projection) {
    loadMatrix(location_projectiontionMatrix, projection);
}

void TerrainShader::loadShineVariables(float damper, float reflectivity) {
    loadFloat(location_shineDamper, damper);
    loadFloat(location_reflectivity, reflectivity);
}

void TerrainShader::getAllUniformLocations() {
    location_transformationMatrix = getUniformLocation("transformationMatrix");
    location_projectiontionMatrix = getUniformLocation("projectionMatrix");
    location_viewMatrix = getUniformLocation("viewMatrix");
    location_shineDamper = getUniformLocation("shineDamper");
    location_reflectivity = getUniformLocation("reflectivity");
    location_skyColour = getUniformLocation("skyColour");
    location_backgroundTexture = getUniformLocation("backgroundTexture");
    location_rTexture = getUniformLocation("rTexture");
    location_gTexture = getUniformLocation("gTexture");
    location_bTexture = getUniformLocation("bTexture");
    location_blendMap = getUniformLocation("blendMap");

    location_lightPosition = new GLint[MAX_LIGHTS];
    location_lightColour = new GLint[MAX_LIGHTS];
    location_attenuation = new GLint[MAX_LIGHTS];
    for(unsigned int i=0; i<MAX_LIGHTS; i++) {
        char locationName[50];
        sprintf(locationName, "lightPosition[%d]", i);
        location_lightPosition[i] = getUniformLocation(locationName);
        sprintf(locationName, "lightColour[%d]", i);
        location_lightColour[i] = getUniformLocation(locationName);
        sprintf(locationName, "attenuation[%d]", i);
        location_attenuation[i] = getUniformLocation(locationName);
    }
}

void TerrainShader::loadSkyColour(float r, float g, float b) {
    loadVector(location_skyColour, glm::vec3(r, g, b));
}

void TerrainShader::loadLights(std::vector<Light *> * lights) {
    for(unsigned int i = 0; i < MAX_LIGHTS; i++) {
        if(i < lights->size()) {
            Light * light = (*lights)[i];
            loadVector(location_lightColour[i], light->getColour());
            loadVector(location_lightPosition[i], light->getPosition());
            loadVector(location_attenuation[i], light->getAttenuation());
        }
        else {
            loadVector(location_lightColour[i], glm::vec3(0, 0, 0));
            loadVector(location_lightPosition[i], glm::vec3(0, 0, 0));
            loadVector(location_attenuation[i], glm::vec3(1, 0, 0));
        }

    }
}

void TerrainShader::connectTextureUnits() {
    loadInt(location_backgroundTexture, 0);
    loadInt(location_rTexture, 1);
    loadInt(location_gTexture, 2);
    loadInt(location_bTexture, 3);
    loadInt(location_blendMap, 4);
}
