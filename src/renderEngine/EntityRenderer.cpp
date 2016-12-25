/*
 * Renderer.cpp
 *
 *  Created on: 28 mar 2016
 *      Author: lorenzo
 */

#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(StaticShader * shader, glm::mat4 projectionMatrix) {
    this->shader = shader;
    shader->start();
    shader->loadProjectionMatrix(projectionMatrix);
    shader->stop();
}

EntityRenderer::~EntityRenderer() {
}

void EntityRenderer::render(std::vector<TModelEntities> * entities) {
    for(unsigned int i = 0; i < entities->size(); i++) {
        TexturedModel * model = (*entities)[i].texturedModel;
        prepareTexturedModel(model);
        std::vector<Entity *> batch = (*entities)[i].entities;
        for(unsigned int j = 0; j < batch.size(); j++){
            prepareInstance(batch[j]);
            glDrawElements(GL_TRIANGLES, model->getRawModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        unbindTexturedModel();
    }

}

void EntityRenderer::prepareTexturedModel(TexturedModel* model) {
    RawModel * rawModel = model->getRawModel();
    glBindVertexArray(rawModel->getVaoID());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    ModelTexture * texture = model->getTexture();
    shader->loadNumberOfRows(texture->getNumberOfRows());
    if(texture->isHasTransparency()) {
        disableCulling();
    }
    shader->loadFakeLightingVariable(texture->isUseFakeLighting());
    shader->loadShineVariables(texture->getShineDamper(), texture->getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model->getTexture()->getID());
}

void EntityRenderer::unbindTexturedModel() {
    enableCulling();
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void EntityRenderer::enableCulling() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void EntityRenderer::disableCulling() {
    glDisable(GL_CULL_FACE);
}

void EntityRenderer::prepareInstance(Entity* entity) {
    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotX(), entity->getRotY(), entity->getRotZ(), entity->getScale());
    shader->loadTransformationMatrix(transformationMatrix);
    shader->loadOffset(entity->getTextureXOffset(), entity->getTextureYOffset());
}
