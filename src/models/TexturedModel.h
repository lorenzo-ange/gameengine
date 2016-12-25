/*
 * TexturedModel.h
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#ifndef MODELS_TEXTUREDMODEL_H_
#define MODELS_TEXTUREDMODEL_H_

#include "RawModel.h"
#include "../textures/ModelTexture.h"

class TexturedModel {
public:
    TexturedModel(RawModel * model, ModelTexture * texture);
    virtual ~TexturedModel();

    RawModel * getRawModel() {
        return rawModel;
    }

    ModelTexture * getTexture() {
        return texture;
    }

private:
    RawModel * rawModel;
    ModelTexture * texture;
};

#endif /* MODELS_TEXTUREDMODEL_H_ */
