/*
 * TextureLoader.h
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#ifndef TEXTURES_LODEPNG_TEXTURELOADER_H_
#define TEXTURES_LODEPNG_TEXTURELOADER_H_

#include "TextureData.h"
#include <stdio.h>
#include <GL/glew.h>

class TextureLoader {
public:
    TextureLoader();
    virtual ~TextureLoader();

    static GLuint getTexture(const char* filename);
};

#endif /* TEXTURES_LODEPNG_TEXTURELOADER_H_ */
