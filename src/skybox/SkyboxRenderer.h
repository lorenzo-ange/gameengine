/*
 * SkyboxRenderer.h
 *
 *  Created on: 10 apr 2016
 *      Author: lorenzo
 */

#ifndef SKYBOX_SKYBOXRENDERER_H_
#define SKYBOX_SKYBOXRENDERER_H_

#include "SkyboxShader.h"
#include "../models/RawModel.h"

class SkyboxRenderer {
public:
    SkyboxRenderer(Loader * loader, glm::mat4 projectionMatrix);
    virtual ~SkyboxRenderer();

    void render(Camera * camera, float r, float g, float b);
    void cleanUp();

private:
    static const float SIZE;
    static const float VERTICES[108];
    static const char * TEXTURE_FILES[6];
    static const char * NIGHT_TEXTURE_FILES[6];

    RawModel * cube;
    GLuint texture;
    GLuint nightTexture;
    SkyboxShader * shader;
    float time;

    void bindTextures();
};

#endif /* SKYBOX_SKYBOXRENDERER_H_ */
