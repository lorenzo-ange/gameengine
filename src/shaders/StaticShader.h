/*
 * StaticShader.h
 *
 *  Created on: 29 mar 2016
 *      Author: lorenzo
 */

#ifndef SHADERS_STATICSHADER_H_
#define SHADERS_STATICSHADER_H_

#include <glm/glm.hpp>

#include "../entities/Camera.h"
#include "../entities/Light.h"
#include "../toolbox/Maths.h"
#include "ShaderProgram.h"

class StaticShader: public ShaderProgram {
public:
    StaticShader();
    virtual ~StaticShader();

    void loadTransformationMatrix(glm::mat4 matrix);
    void loadViewMatrix(Camera * camera);
    void loadProjectionMatrix(glm::mat4 projection);
    void loadLights(std::vector<Light *> * lights);
    void loadShineVariables(float damper, float reflectivity);
    void loadFakeLightingVariable(bool useFake);
    void loadSkyColour(float r, float g, float b);
    void loadNumberOfRows(int numberOfRows);
    void loadOffset(float x, float y);

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
    GLint location_useFakeLighting;
    GLint location_skyColour;
    GLint location_numberOfRows;
    GLint location_offset;

};

#endif /* SHADERS_STATICSHADER_H_ */
