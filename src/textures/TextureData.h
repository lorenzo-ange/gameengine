/*
 * TextureData.h
 *
 *  Created on: 10 apr 2016
 *      Author: lorenzo
 */

#ifndef TEXTURES_TEXTUREDATA_H_
#define TEXTURES_TEXTUREDATA_H_
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <vector>

class TextureData {
public:
    TextureData(const char * filename);
    virtual ~TextureData();

    const std::vector<unsigned char> * getBuffer() const {
        return &buffer;
    }

    unsigned int getHeight() const {
        return height;
    }

    unsigned int getWidth() const {
        return width;
    }

private:
    unsigned int width;
    unsigned int height;
    std::vector<unsigned char> buffer;
};

#endif /* TEXTURES_TEXTUREDATA_H_ */
