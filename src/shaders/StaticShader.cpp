/*
 * StaticShader.cpp
 *
 *  Created on: 29 mar 2016
 *      Author: lorenzo
 */

#include "StaticShader.h"

const unsigned int StaticShader::MAX_LIGHTS = 4;
const char * StaticShader::VERTEX_FILE = "src/shaders/vertexShader.txt";
const char * StaticShader::FRAGMENT_FILE = "src/shaders/fragmentShader.txt";

StaticShader::StaticShader() {
    init(VERTEX_FILE, FRAGMENT_FILE);
}

StaticShader::~StaticShader() {
    delete[] location_lightColour;
    delete[] location_lightPosition;
    delete[] location_attenuation;
}

void StaticShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
    bindAttribute(2, "normal");
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
    loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadViewMatrix(Camera * camera) {
    glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
    loadMatrix(location_viewMatrix, viewMatrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 projection) {
    loadMatrix(location_projectiontionMatrix, projection);
}

void StaticShader::loadLights(std::vector<Light *> * lights) {
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

void StaticShader::loadShineVariables(float damper, float reflectivity) {
    loadFloat(location_shineDamper, damper);
    loadFloat(location_reflectivity, reflectivity);
}

void StaticShader::loadFakeLightingVariable(bool useFake) {
    loadBoolean(location_useFakeLighting, useFake);
}

void StaticShader::loadSkyColour(float r, float g, float b) {
    loadVector(location_skyColour, glm::vec3(r, g, b));
}

void StaticShader::loadNumberOfRows(int numberOfRows) {
    loadFloat(location_numberOfRows, (float) numberOfRows);
}

void StaticShader::loadOffset(float x, float y) {
    load2DVector(location_offset, glm::vec2(x, y));
}

void StaticShader::getAllUniformLocations() {
    location_transformationMatrix = getUniformLocation("transformationMatrix");
    location_projectiontionMatrix = getUniformLocation("projectionMatrix");
    location_viewMatrix = getUniformLocation("viewMatrix");
    location_shineDamper = getUniformLocation("shineDamper");
    location_reflectivity = getUniformLocation("reflectivity");
    location_useFakeLighting = getUniformLocation("useFakeLighting");
    location_skyColour = getUniformLocation("skyColour");
    location_numberOfRows = getUniformLocation("numberOfRows");
    location_offset = getUniformLocation("offset");

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
