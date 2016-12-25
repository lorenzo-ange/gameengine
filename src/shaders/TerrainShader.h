/*
 * TerrainShader.h
 *
 *  Created on: 02 apr 2016
 *      Author: lorenzo
 */

#ifndef SHADERS_TERRAINSHADER_H_
#define SHADERS_TERRAINSHADER_H_

#include <glm/glm.hpp>

#include "../entities/Camera.h"
#include "../entities/Light.h"
#include "../toolbox/Maths.h"
#include "ShaderProgram.h"

class TerrainShader: public ShaderProgram {
public:
    TerrainShader();
    virtual ~TerrainShader();

    void loadTransformationMatrix(glm::mat4 matrix);
    void loadViewMatrix(Camera * camera);
    void loadProjectionMatrix(glm::mat4 projection);
    void loadLights(std::vector<Light *> * lights);
    void loadShineVariables(float damper, float reflectivity);
    void loadSkyColour(float r, float g, float b);
    void connectTextureUnits();

protected:
    void bindAttributes();
    void getAllUniformLocations();

private:
    static const unsigned int MAX_LIGHTS;
    static const char * VERTEX_FILE;
    static const char * FRAGMENT_FILE;

    GLint location_transformationMatrix;
    GLint location_projectiontionMatrix;
    GLint location_viewMatrix;
    GLint * location_lightColour;
    GLint * location_lightPosition;
    GLint * location_attenuation;
    GLint location_shineDamper;
    GLint location_reflectivity;
    GLint location_skyColour;
    GLint location_backgroundTexture;
    GLint location_rTexture;
    GLint location_gTexture;
    GLint location_bTexture;
    GLint location_blendMap;

};

#endif /* SHADERS_TERRAINSHADER_H_ */
