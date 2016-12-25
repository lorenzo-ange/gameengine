/*
 * DisplayManager.cpp
 *
 *  Created on: 28 mar 2016
 *      Author: lorenzo
 */

#include "DisplayManager.h"

float DisplayManager::frameTimeSeconds = 0;
const int DisplayManager::WIDTH = 800;
const int DisplayManager::HEIGHT = 600;
const int DisplayManager::FPS_CAP = 60;
const float DisplayManager::MIN_FRAME_TIME = 1000.0f / FPS_CAP;
const char * DisplayManager::TITLE = "3D Game Engine";

SDL_Window * DisplayManager::window;
SDL_GLContext DisplayManager::glContext;

DisplayManager::DisplayManager() {
}

DisplayManager::~DisplayManager() {
}

int DisplayManager::createDisplay() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Couldn't init video: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if(window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    glContext = SDL_GL_CreateContext(window);
    // Set our OpenGL version.
    // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // 3.2 is part of the modern versions of OpenGL, but most video cards would be able to run it
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Turn on double buffering with a 24bit Z buffer.
    // You may need to change this to 16 or 32 for your system
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);

    // Init GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    return 0;
}

void DisplayManager::updateDisplay() {
    static int frametime = 0;
    if (SDL_GetTicks() - frametime < MIN_FRAME_TIME) {
        SDL_Delay(MIN_FRAME_TIME - (SDL_GetTicks() - frametime));
    }
    // printf("frame time : %d\n",  (SDL_GetTicks() - frametime));
    char title[50];
    sprintf(title, "GameEngine - FPS: %d", 1000 / (SDL_GetTicks() - frametime));
    setWindowTitle(title);
    frameTimeSeconds = (SDL_GetTicks() - frametime)/1000.0f;
    frametime = SDL_GetTicks();
    SDL_GL_SwapWindow(window);
}

void DisplayManager::closeDisplay() {
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void DisplayManager::setWindowTitle(const char* title) {
    SDL_SetWindowTitle(window, title);
}
