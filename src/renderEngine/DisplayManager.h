/*
 * DisplayManager.h
 *
 *  Created on: 28 mar 2016
 *      Author: lorenzo
 */

#ifndef RENDERENGINE_DISPLAYMANAGER_H_
#define RENDERENGINE_DISPLAYMANAGER_H_

#include <GL/glew.h>
#include <SDL2/SDL.h>

class DisplayManager {
public:
    DisplayManager();
    virtual ~DisplayManager();
    static int createDisplay();
    static void updateDisplay();
    static void closeDisplay();
    static float getFrameTimeSeconds() {
        return frameTimeSeconds;
    }

    static int getHeight() {
        return HEIGHT;
    }

    static int getWidth() {
        return WIDTH;
    }

private:
    static const int WIDTH;
    static const int HEIGHT;
    static const int FPS_CAP;
    static const float MIN_FRAME_TIME;
    static const char * TITLE;

    static float frameTimeSeconds;
    static SDL_Window *window;
    static SDL_GLContext glContext;

    static void setWindowTitle(const char * title);
};

#endif /* RENDERENGINE_DISPLAYMANAGER_H_ */
