/*
 * TextureData.cpp
 *
 *  Created on: 10 apr 2016
 *      Author: lorenzo
 */

#include "TextureData.h"

TextureData::TextureData(const char * filename) {

    SDL_Surface *surface = IMG_Load(filename);
    if(surface == NULL) {
        fprintf(stderr, "SDL loader error for '%s'", filename);
    }
    else {
        std::vector<unsigned char> tmp((unsigned char *) surface->pixels,
                                       (unsigned char *) surface->pixels + surface->w * surface->h * 4);
        width = (unsigned int) surface->w;
        height = (unsigned int) surface->h;
        for (unsigned int i = 0; i < tmp.size(); i++) {
            buffer.push_back(tmp[i]);
        }
        SDL_FreeSurface(surface);
    }
}

TextureData::~TextureData() {
}

