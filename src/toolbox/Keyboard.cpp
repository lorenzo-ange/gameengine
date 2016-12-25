/*
 * Keyboard.cpp
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#include "Keyboard.h"

Keyboard::Keyboard() {
    for(unsigned int i = 0; i<sizeof(keysDown)/sizeof(bool); i++){
        keysDown[i] = false;
    }

    int i = 0;
    addKeyAssoc(i++, GK_LEFT, SDLK_LEFT);
    addKeyAssoc(i++, GK_UP, SDLK_UP);
    addKeyAssoc(i++, GK_RIGHT, SDLK_RIGHT);
    addKeyAssoc(i++, GK_DOWN, SDLK_DOWN);

    addKeyAssoc(i++, GK_A, SDLK_a);
    addKeyAssoc(i++, GK_D, SDLK_d);
    addKeyAssoc(i++, GK_W, SDLK_w);
    addKeyAssoc(i++, GK_S, SDLK_s);
    addKeyAssoc(i++, GK_Q, SDLK_q);
    addKeyAssoc(i++, GK_N, SDLK_n);
    addKeyAssoc(i++, GK_Y, SDLK_y);

    addKeyAssoc(i++, GK_SPACE, SDLK_SPACE);

}

Keyboard::~Keyboard() {
}

bool Keyboard::isKeyDown(GameKey key) {
    return keysDown[key];
}

void Keyboard::handleSDLEvent(SDL_Event * event) {
    int keyMapLen = sizeof(keyMap)/sizeof(KeyAssoc);

    switch (event->type) {
        case SDL_KEYUP:
            for(int i = 0; i < keyMapLen; i++){
                if(event->key.keysym.sym == keyMap[i].sdlk) {
                    keysDown[keyMap[i].gk] = false;
                }
            }
            break;
         case SDL_KEYDOWN:
             for(int i = 0; i < keyMapLen; i++){
                 if(event->key.keysym.sym == keyMap[i].sdlk) {
                     keysDown[keyMap[i].gk] = true;
                 }
             }
             break;
    }
}

void Keyboard::addKeyAssoc(int index, GameKey gk, int sdlk) {
    keyMap[index].gk = gk;
    keyMap[index].sdlk = sdlk;
}
