/*
 * TexturedModel.cpp
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel * model, ModelTexture * texture) {
    this->rawModel = model;
    this->texture = texture;

}

TexturedModel::~TexturedModel() {
}

