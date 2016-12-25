/*
 * SkyboxShader.h
 *
 *  Created on: 10 apr 2016
 *      Author: lorenzo
 */

#ifndef SKYBOX_SKYBOXSHADER_H_
#define SKYBOX_SKYBOXSHADER_H_

#include "../entities/Camera.h"
#include "../renderEngine/DisplayManager.h"
#include "../toolbox/Maths.h"
#include "../shaders/ShaderProgram.h"

class SkyboxShader : public ShaderProgram {
public:
    SkyboxShader();
    virtual ~SkyboxShader();

    void loadViewMatrix(Camera * camera);
    void loadProjectionMatrix(glm::mat4 projection);
    void loadFogColour(float r, float g, float b);
    void loadBlendFactor(float blendFactor);
    void connectTextureUnits();

protected:
    void bindAttributes();
    void getAllUniformLocations();

private:
    static const char * VERTEX_FILE;
    static const char * FRAGMENT_FILE;
    static const float ROTATION_SPEED;

    GLuint location_projectiontionMatrix;
    GLuint location_viewMatrix;
    GLuint location_fogColour;
    GLuint location_cubeMap;
    GLuint location_cubeMap2;
    GLuint location_blendFactor;

    float rotation;
};

#endif /* SKYBOX_SKYBOXSHADER_H_ */
