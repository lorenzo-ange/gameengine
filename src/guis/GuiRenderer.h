/*
 * GuiRenderer.h
 *
 *  Created on: 06 apr 2016
 *      Author: lorenzo
 */

#ifndef GUIS_GUIRENDERER_H_
#define GUIS_GUIRENDERER_H_

#include <GL/glew.h>
#include <vector>
#include "../renderEngine/Loader.h"
#include "../models/RawModel.h"
#include "GuiTexture.h"
#include "GuiShader.h"
#include "../toolbox/Maths.h"

class GuiRenderer {
public:
    GuiRenderer(Loader * loader);
    virtual ~GuiRenderer();

    void render(std::vector<GuiTexture *> * guis);
    void cleanUp();

private:
    RawModel * quad;
    GuiShader * shader;
};

#endif /* GUIS_GUIRENDERER_H_ */
