/*
 * Keyboard.h
 *
 *  Created on: 30 mar 2016
 *      Author: lorenzo
 */

#ifndef TOOLBOX_KEYBOARD_H_
#define TOOLBOX_KEYBOARD_H_

#include <SDL2/SDL.h>

class Keyboard {
public:
    enum GameKey
        {
          GK_LEFT,
          GK_RIGHT,
          GK_UP,
          GK_DOWN,
          GK_W,
          GK_S,
          GK_A,
          GK_D,
          GK_Q,
          GK_N,
          GK_Y,
          GK_SPACE
        };

    Keyboard();
    virtual ~Keyboard();

    bool isKeyDown(GameKey key);

    void handleSDLEvent(SDL_Event * event);
private:
    struct KeyAssoc {
        GameKey gk;
        int sdlk;
    };
    KeyAssoc keyMap[12];
    bool keysDown[13];

    void addKeyAssoc(int index, GameKey gk, int sdlk);
};

#endif /* TOOLBOX_KEYBOARD_H_ */
