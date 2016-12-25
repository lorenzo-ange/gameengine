/*
 * Renderer.h
 *
 *  Created on: 28 mar 2016
 *      Author: lorenzo
 */

#ifndef RENDERENGINE_ENTITYRENDERER_H_
#define RENDERENGINE_ENTITYRENDERER_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "../models/RawModel.h"
#include "../models/TexturedModel.h"
#include "../shaders/StaticShader.h"
#include "../toolbox/Maths.h"
#include "../entities/Entity.h"

struct TModelEntities {
    TexturedModel * texturedModel;
    std::vector<Entity *> entities;
};

class EntityRenderer {
public:
    EntityRenderer(StaticShader * shader, glm::mat4 projectionMatrix);
    virtual ~EntityRenderer();

    static void enableCulling();
    static void disableCulling();

    void render(std::vector<TModelEntities> * entities);

private:
    StaticShader * shader;

    void prepareTexturedModel(TexturedModel * model);
    void unbindTexturedModel();
    void prepareInstance(Entity * entity);
};

#endif /* RENDERENGINE_ENTITYRENDERER_H_ */
