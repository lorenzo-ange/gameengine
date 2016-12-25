/*
 * GuiRenderer.cpp
 *
 *  Created on: 06 apr 2016
 *      Author: lorenzo
 */

#include "GuiRenderer.h"

GuiRenderer::GuiRenderer(Loader * loader) {
    float positions[] = { -1, 1, -1, -1, 1, 1, 1, -1 };
    quad = new RawModel(loader->loadToVAO(positions, sizeof(positions)/sizeof(float), 2));
    shader = new GuiShader();
}

GuiRenderer::~GuiRenderer() {
    delete quad;
    delete shader;
}

void GuiRenderer::render(std::vector<GuiTexture *> * guis) {
    shader->start();
    glBindVertexArray(quad->getVaoID());
    glEnableVertexAttribArray(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    for(unsigned int i = 0; i < guis->size(); i++) {
        GuiTexture * gui = (*guis)[i];
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gui->getTexture());
        glm::mat4 matrix = Maths::createTransformationMatrix(gui->getPosition(), gui->getScale());
        shader->loadTransformationMatrix(matrix);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, quad->getVertexCount());
    }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader->stop();
}

void GuiRenderer::cleanUp() {
    shader->cleanUp();
}
