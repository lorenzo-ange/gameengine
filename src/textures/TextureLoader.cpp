/*
 * TextureLoader.cpp
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#include "TextureLoader.h"

TextureLoader::TextureLoader() {
}

TextureLoader::~TextureLoader() {
}

GLuint TextureLoader::getTexture(const char* filename) {

    TextureData data(filename);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, data.getWidth(), data.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &(*data.getBuffer())[0]);

    return textureID;
}
